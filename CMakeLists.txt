cmake_minimum_required(VERSION 3.10)
project(face_detect)

set(OpenCV_DIR "/usr/include/opencv4/")
find_package(OpenCV REQUIRED)

set(ONNXRUNTIME_DIR "/opt/onnxruntime/")
find_library(ONNXRUNTIME_LIB onnxruntime HINTS ${ONNXRUNTIME_DIR}/lib)

set(FACE_DETECT_DIR "/home/tawerka/Projects/sneaky-face/")
include_directories(${FACE_DETECT_DIR})

include_directories(${ONNXRUNTIME_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

link_libraries(${OpenCV_LIBRARIES} ${ONNXRUNTIME_LIB})

add_executable(main utils/main.cpp)
