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

extern const char *class_names[];

std::vector<std::string> getClassName();

int process(std::string model_path, std::string path_to_video, std::string path_to_save, std::vector<std::string> class_nums, std::vector<int> blur_rate);

#endif // FACE_DETECT_H
