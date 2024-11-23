QT += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    face_detect.cpp \
    main.cpp \
    mainwindow.cpp \
    videowindow.cpp

HEADERS += \
    face_detect.h \
    mainwindow.h \
    videowindow.h

FORMS += \
    mainwindow.ui \
    videowindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Add paths to ONNX Runtime and OpenCV
INCLUDEPATH += /home/gekcer/installs/onnxruntime-linux-x64-1.20.1/include \
               /usr/include/opencv4

LIBS += -L/home/gekcer/installs/onnxruntime-linux-x64-1.20.1/lib -lonnxruntime \
        -L/usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio
