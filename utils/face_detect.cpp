const char *class_names[] = {
    "face",         "bicycle",    "car",           "motorcycle",    "airplane",     "bus",           "train",
    "truck",          "boat",       "traffic light", "fire hydrant",  "stop sign",    "parking meter", "bench",
    "bird",           "cat",        "dog",           "horse",         "sheep",        "cow",           "elephant",
    "bear",           "zebra",      "giraffe",       "backpack",      "umbrella",     "handbag",       "tie",
    "suitcase",       "frisbee",    "skis",          "snowboard",     "sports ball",  "kite",          "baseball bat",
    "baseball glove", "skateboard", "surfboard",     "tennis racket", "bottle",       "wine glass",    "cup",
    "fork",           "knife",      "spoon",         "bowl",          "banana",       "apple",         "sandwich",
    "orange",         "broccoli",   "carrot",        "hot dog",       "pizza",        "donut",         "cake",
    "chair",          "couch",      "potted plant",  "bed",           "dining table", "toilet",        "tv",
    "laptop",         "mouse",      "remote",        "keyboard",      "cell phone",   "microwave",     "oven",
    "toaster",        "sink",       "refrigerator",  "book",          "clock",        "vase",          "scissors",
    "teddy bear",     "hair drier", "toothbrush"};


#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <onnxruntime_cxx_api.h>
#include <opencv2/dnn/dnn.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;
using Array = vector<float>;
using Shape = vector<long>;


string model_path = "../models/yolov10n-face.onnx";


int main(int, char**)
{

    Mat frame;
    VideoCapture cap;

    bool use_cuda = false;
    Size size(640,640);

    Array input_data(640 * 640 * 3);  // Пример: массив для 640x640 RGB изображения
    Shape input_shape = {1, 3, 640, 640}; // Пример формы для входа: batch=1, channels=3, height=640, width=640

    int deviceID = 2;             
    int apiID = cv::CAP_ANY;     

    cap.open(deviceID, apiID);

    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;


    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "YOLOv8n");
    Ort::SessionOptions options;
    Ort::Session session(env, model_path.c_str(), options);

    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    const char *input_names[] = {"images"};
    const char *output_names[] = {"output0"};

    for (;;)
    {

        cap.read(frame);

        cv::resize(frame, frame, size);

        for (int i = 0; i < frame.rows; ++i) {
            for (int j = 0; j < frame.cols; ++j) {
                Vec3b pixel = frame.at<Vec3b>(i, j);
                input_data[i * frame.cols * 3 + j * 3 + 0] = pixel[0] / 255.0f; // R
                input_data[i * frame.cols * 3 + j * 3 + 1] = pixel[1] / 255.0f; // G
                input_data[i * frame.cols * 3 + j * 3 + 2] = pixel[2] / 255.0f; // B
            }
        }

        Shape shape = {1, frame.channels(), frame.rows, frame.cols};
        cv::Mat nchw = cv::dnn::blobFromImage(frame, 1.0, {}, {}, true) / 255.f;
        Array array(nchw.ptr<float>(), nchw.ptr<float>() + nchw.total());

        
        auto input = Ort::Value::CreateTensor<float>(memory_info, array.data(), array.size(), shape.data(), shape.size());

        auto output = session.Run({}, input_names, &input, 1, output_names, 1);

        shape = output[0].GetTensorTypeAndShapeInfo().GetShape();

        int num_boxes = output.size();
        auto ptr = output[0].GetTensorData<float>();


        for (size_t i = 0; i < shape[1]; i++){
            
            float* data = output[0].GetTensorMutableData<float>() + i * 6;

                    if (data != nullptr) {
                        int x = data[0];
                        int y = data[1];
                        int x_max = data[2];
                        int y_max = data[3];
                        int c = data[5];
                    
                        auto name = string(class_names[c]) + ":" + to_string(data[4]);
                        if (data[4] > 0.3) {
                        cv::rectangle(frame, cv::Point(x, y), cv::Point(x_max, y_max), cv::Scalar(255, 0, 0), 2);
                        cv::putText(frame, name, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 255), 2);

                        } 
                        

        } 
        }

        cout << "Shape of frame: " << frame.rows << " x " << frame.cols << endl;

        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }


        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }

    return 0;
}

