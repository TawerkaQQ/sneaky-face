package com.cybergarden.fbi

import android.content.Context
import android.graphics.Bitmap
import android.os.SystemClock
import android.util.Log
import com.cybergarden.fbi.MetaData.extractNamesFromLabelFile
import com.cybergarden.fbi.MetaData.extractNamesFromMetadata
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import org.tensorflow.lite.DataType
import org.tensorflow.lite.Interpreter
import org.tensorflow.lite.gpu.CompatibilityList
import org.tensorflow.lite.gpu.GpuDelegate
import org.tensorflow.lite.support.common.FileUtil
import org.tensorflow.lite.support.common.ops.CastOp
import org.tensorflow.lite.support.common.ops.NormalizeOp
import org.tensorflow.lite.support.image.ImageProcessor
import org.tensorflow.lite.support.image.TensorImage
import org.tensorflow.lite.support.tensorbuffer.TensorBuffer
import kotlin.math.abs

class Detector(
    private val context: Context,
    private val modelPath: String,
    private val labelPath: String?,
    private val detectorListener: DetectorListener,
    private val message: (String) -> Unit
) {
    private var interpreter: Interpreter
    private var labels = mutableListOf<String>()

    private var tensorWidth = 0
    private var tensorHeight = 0
    private var numChannel = 0
    private var numElements = 0

    private var isAlreadyCancelledInterpreter = false

    private val imageProcessor = ImageProcessor.Builder()
        .add(NormalizeOp(INPUT_MEAN, INPUT_STANDARD_DEVIATION))
        .add(CastOp(INPUT_IMAGE_TYPE))
        .build()

    init {
        val options = Interpreter.Options().apply{
            this.setNumThreads(4)
            this.setCancellable(true)
        }

        val model = FileUtil.loadMappedFile(context, modelPath)
        interpreter = Interpreter(model, options)

        labels.addAll(extractNamesFromMetadata(model))
        if (labels.isEmpty()) {
            if (labelPath == null) {
                message("Model not contains metadata, provide LABELS_PATH in Constants.kt")
                labels.addAll(MetaData.TEMP_CLASSES)
            } else {
                labels.addAll(extractNamesFromLabelFile(context, labelPath))
            }
        }

        labels.forEach(::println)

        val inputShape = interpreter.getInputTensor(0)?.shape()
        val outputShape = interpreter.getOutputTensor(0)?.shape()

        if (inputShape != null) {
            tensorWidth = inputShape[1]
            tensorHeight = inputShape[2]

            // If in case input shape is in format of [1, 3, ..., ...]
            if (inputShape[1] == 3) {
                tensorWidth = inputShape[2]
                tensorHeight = inputShape[3]
            }
        }

        if (outputShape != null) {
            numElements = outputShape[1]
            numChannel = outputShape[2]
        }
    }

    fun restart(useGpu: Boolean = false) {
        close()

        val options = if (useGpu) {
            val compatList = CompatibilityList()
            Interpreter.Options().apply {
                if(compatList.isDelegateSupportedOnThisDevice){
                    val delegateOptions = compatList.bestOptionsForThisDevice
                    this.addDelegate(GpuDelegate(delegateOptions))
                    this.setCancellable(true)
                } else {
                    this.setNumThreads(4)
                    this.setCancellable(true)
                }
            }
        } else {
            Interpreter.Options().apply {
                this.setNumThreads(4)
                this.setCancellable(true)
            }
        }

        val model = FileUtil.loadMappedFile(context, modelPath)
        interpreter = Interpreter(model, options)
    }

//    fun close() {
//        interpreter.close()
//    }

    private fun cancelInterpreter(interpreterCancelled: (() -> Unit)) {
        CoroutineScope(Dispatchers.IO).launch {
            isAlreadyCancelledInterpreter = true
            interpreter.setCancelled(true)
            delay(500) //for cases when cancel of interpreter executes so long time
            interpreterCancelled.invoke()
        }
    }

    fun close(interpreterCancelled: (() -> Unit)? = null) {
        cancelInterpreter {
            CoroutineScope(Dispatchers.IO).launch {
            delay(150)
            interpreter.close()
                delay(1000)
                interpreterCancelled?.invoke()
            }
        }
    }

    fun detect(frame: Bitmap) {
        if (tensorWidth == 0
            || tensorHeight == 0
            || numChannel == 0
            || numElements == 0) return

        if (isAlreadyCancelledInterpreter) return

        var inferenceTime = SystemClock.uptimeMillis()

        val resizedBitmap = Bitmap.createScaledBitmap(frame, tensorWidth, tensorHeight, false)

        val tensorImage = TensorImage(INPUT_IMAGE_TYPE)
        tensorImage.load(resizedBitmap)
        val processedImage = imageProcessor.process(tensorImage)
        val imageBuffer = processedImage.buffer

        val output = TensorBuffer.createFixedSize(intArrayOf(1, numChannel, numElements), OUTPUT_IMAGE_TYPE)
        try {
            interpreter.run(imageBuffer, output.buffer)
        } catch (e: Exception) {
            Log.w("DetectorError", "Failed run Interpreter: ${e.message}")
        }

        val bestBoxes = bestBox(output.floatArray)
        inferenceTime = SystemClock.uptimeMillis() - inferenceTime

        if (bestBoxes.isEmpty()) {
            detectorListener.onEmptyDetect()
            return
        }

        detectorListener.onDetect(bestBoxes, inferenceTime)
    }

    private fun bestBox(array: FloatArray) : List<BoundingBox> {
        val boundingBoxes = mutableListOf<BoundingBox>()
        for (r in 0 until numElements) {
            val cnf = array[r * numChannel + 4]
            if (cnf > CONFIDENCE_THRESHOLD) {
                val x1 = array[r * numChannel]
                val y1 = array[r * numChannel + 1]
                val x2 = array[r * numChannel + 2]
                val y2 = array[r * numChannel + 3]
                val cls = array[r * numChannel + 5].toInt()
                val clsName = "labels[cls]"
                boundingBoxes.add(
                    BoundingBox(
                        x1 = x1, y1 = y1, x2 = x2, y2 = y2,
                        cnf = cnf, cls = cls, clsName = clsName
                    )
                )
            }
        }
        return boundingBoxes
    }

    interface DetectorListener {
        fun onEmptyDetect()
        fun onDetect(boundingBoxes: List<BoundingBox>, inferenceTime: Long)
    }

    companion object {
        private const val INPUT_MEAN = 0f
        private const val INPUT_STANDARD_DEVIATION = 255f
        private val INPUT_IMAGE_TYPE = DataType.FLOAT32
        private val OUTPUT_IMAGE_TYPE = DataType.FLOAT32
        private const val CONFIDENCE_THRESHOLD = 0.5F
    }
}