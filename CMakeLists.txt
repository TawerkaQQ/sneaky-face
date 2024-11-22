cmake_minimum_required(VERSION 3.10)
project(face_detect)

set(OpenCV_DIR "/usr/include/opencv4/")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBRARIES})

add_executable(face_detect utils/face_detect.cpp)