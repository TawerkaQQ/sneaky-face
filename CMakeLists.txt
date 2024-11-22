cmake_minimum_required(VERSION 3.10)
project(face_detect)

set(OpenCV_DIR "/usr/include/opencv4/")
find_package(OpenCV REQUIRED)

set(ONNXRUNTIME_DIR "/opt/onnxruntime/")
find_library(ONNXRUNTIME_LIB onnxruntime HINTS ${ONNXRUNTIME_DIR}/lib)

include_directories(${ONNXRUNTIME_DIR}/include)

include_directories(${OpenCV_INCLUDE_DIRS})

link_libraries(${OpenCV_LIBRARIES} ${ONNXRUNTIME_LIB})

add_executable(face_detect utils/face_detect.cpp)
