package com.cybergarden.fbi.ui

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BlurMaskFilter
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.DrawFilter
import android.graphics.Paint
import android.graphics.Rect
import android.graphics.RectF
import android.graphics.RenderNode
import android.renderscript.Allocation
import android.renderscript.RenderScript
import android.renderscript.ScriptIntrinsicBlur
import android.util.AttributeSet
import android.view.View
import androidx.core.content.res.ResourcesCompat
import com.cybergarden.fbi.BoundingBox
import com.cybergarden.fbi.R

class OverlayView(context: Context, attrs: AttributeSet?) : View(context, attrs) {

    private var results = listOf<BoundingBox>()
    private var boxPaint = Paint()
    private var textBackgroundPaint = Paint()
    private var textPaint = Paint()

    private var bounds = Rect()

    init {
        initPaints()
    }

    fun clear() {
        results = listOf()
        textPaint.reset()
        textBackgroundPaint.reset()
        boxPaint.reset()
        invalidate()
        initPaints()
    }

    private fun initPaints() {
        textBackgroundPaint.color = 0x00000000
        textBackgroundPaint.style = Paint.Style.FILL
        textBackgroundPaint.textSize = 36f

        textPaint.color = 0x00000000
        textPaint.style = Paint.Style.STROKE
        textPaint.textSize = 36f

        boxPaint.color = Color.argb(228, 194, 194, 194)
        boxPaint.strokeWidth = 6F
        boxPaint.style = Paint.Style.FILL
//        boxPaint.setShadowLayer(10f, 20f, 20f, Color.GRAY)
        boxPaint.maskFilter = BlurMaskFilter(10f, BlurMaskFilter.Blur.NORMAL)
    }

    override fun draw(canvas: Canvas) {
        super.draw(canvas)

        results.forEach {

            val left = it.x1 * width
            val top = it.y1 * height
            val right = it.x2 * width
            val bottom = it.y2 * height


            canvas.drawRoundRect(left, top, right, bottom, 16f, 16f, boxPaint)
            canvas.drawRoundRect(left, top, right, bottom, 16f, 16f, boxPaint)

            val drawableText = "${it.clsName} ${Math.round(it.cnf * 100.0) / 100.0}"

            textBackgroundPaint.getTextBounds(drawableText, 0, drawableText.length, bounds)
            val textWidth = bounds.width()
            val textHeight = bounds.height()

            val textBackgroundRect = RectF(
                left,
                top,
                left + textWidth + BOUNDING_RECT_TEXT_PADDING,
                top + textHeight + BOUNDING_RECT_TEXT_PADDING
            )
            canvas.drawRoundRect(textBackgroundRect, 8f, 8f, textBackgroundPaint)

            canvas.drawText(drawableText, left, top + textHeight, textPaint)

        }
    }

    fun setResults(boundingBoxes: List<BoundingBox>) {
        results = boundingBoxes
        invalidate()
    }

    companion object {
        private const val BOUNDING_RECT_TEXT_PADDING = 8
    }
}