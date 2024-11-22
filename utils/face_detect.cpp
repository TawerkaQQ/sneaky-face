const char *class_names[] = {
    "person",         "bicycle",    "car",           "motorcycle",    "airplane",     "bus",           "train",
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
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;
using Array = std::vector<float>;
using Shape = std::vector<long>;


std::string model_path = "/home/tawerka/Projects/sneaky-face/models/yolov10n-face.onnx";


int main(int, char**)
{

    Mat frame;
    VideoCapture cap;

    bool use_cuda = false;
    Size size(640,640);

    Array input_data(640 * 640 * 3);  // Пример: массив для 640x640 RGB изображения
    Shape input_shape = {1, 3, 640, 640}; // Пример формы для входа: batch=1, channels=3, height=640, width=640


    
    int deviceID = 0;             
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
    auto input = Ort::Value::CreateTensor<float>(memory_info, input_data.data(), input_data.size(), input_shape.data(), input_shape.size());


    const char *input_names[] = {"images"};
    const char *output_names[] = {"output0"};
    auto output = session.Run({}, input_names, &input, 1, output_names, 1);
    Shape shape = output[0].GetTensorTypeAndShapeInfo().GetShape();
    auto ptr = output[0].GetTensorData<float>();

    for (;;)
    {

        cap.read(frame);

        cv::resize(frame, frame, size);


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

