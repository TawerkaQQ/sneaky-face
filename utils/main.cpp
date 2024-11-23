#include <utils/face_detect.cpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace std;

int process(string model_path, string path_to_video, string path_to_save, vector<string> class_nums, vector<int> blur_rate);

int main(){

    string model_path = "../models/yolov10n-face.onnx";
    string path_to_video = "/home/tawerka/Projects/sneaky-face/example_data/human_faces_2.mp4";
    string path_to_save = "/home/tawerka/Projects/sneaky-face/output_video.mp4";
    vector<string> class_nums = {"face", "bicycle","car", "motorcycle", "airplane", "bus", "train",};
    vector<int> blur_rate = {1,3, 54, 5, 6, 7};

    process(model_path, path_to_video, path_to_save, class_nums, blur_rate);

}