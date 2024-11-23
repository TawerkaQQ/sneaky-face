#ifndef FACE_DETECT_H
#define FACE_DETECT_H

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

using namespace std;

extern const char *class_names[];

vector<string> getClassName();
vector<string> getModelName();

int process_video(string model_path, string path_to_video, string path_to_save, vector<string> class_nums, int blur_rate, int& progress_bar);

int process_rtp(string model_path, string path_to_video, string path_to_save, vector<string> class_nums, int blur_rate, int& progress_bar); 

#endif // FACE_DETECT_H
