cmake_minimum_required(VERSION 3.15)

project(sneaky_face)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5 components
find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)

set(OpenCV_DIR "/usr/include/opencv4/")
find_package(OpenCV REQUIRED)

set(ONNXRUNTIME_DIR "/opt/onnxruntime/")

find_library(ONNXRUNTIME_LIB onnxruntime HINTS ${ONNXRUNTIME_DIR}/lib)


include_directories(${ONNXRUNTIME_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

link_libraries(${OpenCV_LIBRARIES} ${ONNXRUNTIME_LIB})

# Enable automatic MOC and UIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# List of source files
set(SOURCES
    sneaky_face/main.cpp
    sneaky_face/mainwindow.cpp
    sneaky_face/videowindow.cpp
    sneaky_face/face_detect.cpp
    sneaky_face/mainwindow.ui
    sneaky_face/videowindow.ui
)

set(HEADERS
    sneaky_face/mainwindow.h
    sneaky_face/videowindow.h
    sneaky_face/face_detect.h
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::MultimediaWidgets
    ${OpenCV_LIBS}
    ${ONNXRUNTIME_LIB}
)

# Include OpenCV directories
target_include_directories(${PROJECT_NAME}
    PRIVATE ${OpenCV_INCLUDE_DIRS}
    PRIVATE ${ONNXRUNTIME_DIR}/include
)
