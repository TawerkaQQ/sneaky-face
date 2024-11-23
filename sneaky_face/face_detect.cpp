#include <vector>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <onnxruntime_cxx_api.h>
#include <opencv2/dnn/dnn.hpp>
#include <iostream>
#include <stdio.h>

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

std::vector<std::string> getClassName() {
    std::vector<std::string> classes;
    int classes_count = sizeof(class_names) / sizeof(class_names[0]);
    for (int i = 0; i < classes_count; i++) {
        classes.push_back(class_names[i]);
    }
    return classes;
}

using namespace cv;
using namespace std;
using Array = vector<float>;
using Shape = vector<long>;



// false == RTP, true == Video
bool type_video = false;

int process(string model_path, string path_to_video, string path_to_save, vector<string> class_nums, vector<int> blur_rate) // string model_path, string path_to_video, string path_to_save, array<string> class_nums, float blur_rate
{

    Mat frame;
    VideoCapture cap;
    bool use_cuda = false;
    Size size(640,640);

    Array input_data(640 * 640 * 3);  // Пример: массив для 640x640 RGB изображения
    Shape input_shape = {1, 3, 640, 640}; // Пример формы для входа: batch=1, channels=3, height=640, width=640
    int apiID = cv::CAP_ANY;

    VideoWriter writer;
    int codec = VideoWriter::fourcc('a', 'v', 'c', '1');

    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
    cout << "Start processing video with " << total_frames << " frames" << endl;

    if (type_video) {
        int deviceID = 0;
        cap.open(deviceID, apiID);
    }
    else {
        cap.open(path_to_video);
    }


    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    double fps = cap.get(CAP_PROP_FPS);
    writer.open(path_to_save, codec, fps, size);

    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;


    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "YOLOv8n");
    Ort::SessionOptions options;
    Ort::Session session(env, model_path.c_str(), options);

    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    const char *input_names[] = {"images"};
    const char *output_names[] = {"output0"};
    int frame_count = 0;


    bool success = true;

    for (;;)
    {

        success = cap.read(frame);

        if (!success || frame.empty()) {
            cout << "End of video reached or error reading frame" << endl;
            break;
        }

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
                        if (data[4] > 0.15) {
                            Rect roi(x, y, x_max - x, y_max - y);

                            roi = roi & Rect(0, 0, frame.cols, frame.rows);

                            if (roi.width > 0 && roi.height > 0) {

                                Mat roi_img = frame(roi);

                                Mat blurred;
                                GaussianBlur(roi_img, blurred, Size(45, 45), 30);


                                blurred.copyTo(frame(roi));
                            }
                        }
        }
        }

        cout << "Shape of frame: " << frame.rows << " x " << frame.cols << endl;

        writer.write(frame);
        frame_count++;

        if (frame_count % 15 == 0) { // Показываем прогресс каждые 30 кадров
            cout << "Processed " << frame_count << " of " << total_frames << " frames" << endl;
        }


        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;


    }

    cout << "Write complete !" << endl;
    cap.release();
    writer.release();
    destroyAllWindows();

    return 0;
}