#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "face_detect.h"
#include <QDebug>
#include <string>
#include <vector>
#include <QImage>
#include <QPixmap>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <onnxruntime_cxx_api.h>
#include <opencv2/dnn/dnn.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

using Array = vector<float>;
using Shape = vector<long>;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , videoWindow(nullptr)
{
    ui->setupUi(this);
    // INPUT BUTTON
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::processVideoButton);


    std::vector<std::string> classes = getClassName();
    for (const std::string& class_name : classes) {
        ui->comboBox->addItem(QString::fromStdString(class_name));
    }

    std::vector<std::string> models = getModelName();
    for (const std::string& model_name : models) {
        ui->comboBox_2->addItem(QString::fromStdString(model_name));
    }

    // WATCH_VIDEO BUTTON
//    connect(ui->pushButton2, &QPushButton::clicked, this, &MainWindow::openVideoWindow);

    // RTP_VIDEO_BUTTON
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::processRTPVideoButton);
    // STOP_BUTTON
    connect(ui->stop_button, &QPushButton::clicked, this, &MainWindow::stop_all);

    // RESUME_BUTTON
    connect(ui->resumeButton, &QPushButton::clicked, this, &MainWindow::resume);

    // BLUR_SLIDER
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::blur_slider);

}


MainWindow::~MainWindow() {
    delete ui;
    delete videoWindow;
}

// PATH_VIDEO_PROCESS
void MainWindow::processVideoButton() {
    qDebug() << "processVideoButton pushed";
    // выбор видео для обработки
    QString videoFile = QFileDialog::getOpenFileName(
                this,
                tr("Выбор видео для обработки"),
                QString(),
                tr("Video Files (*.mp4 *.avi *.mkv)")
    );
    if (videoFile.isEmpty()){
        qDebug() << "Не выбрано видео";
        return;
    }

    // выбор модели
    QString modelName = QFileDialog::getOpenFileName(
                this,
                tr("Выбор модели для обработки"),
                QString(),
                tr("ONNX Models (*.onnx)")
    );
    if (modelName.isEmpty()){
        qDebug() << "Не выбрана модель";
        return;
    }

    QString outputFilePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Processed Video"),
            QString(),
            tr("Video Files (*.mp4 *.avi *.mkv)")
        );
        if (outputFilePath.isEmpty()) {
            qDebug() << "Не указано место сохранения";
            return;
        }

    QString className = ui->comboBox->currentText();
    if (className.isEmpty()){
        qDebug() << "Не выбран класс";
        return;
    }

    qDebug() << "видео" << videoFile;
    qDebug() << "аут" << outputFilePath;
    qDebug() << "модель" << modelName;
    qDebug() << "класс" << className;

    int blurRate = 100;

    classesVector.clear();
    blurVector.clear();
    classesVector.push_back(className.toStdString());
    blurVector.push_back(blurRate);

    string model_path = "../models/yolov10n-face.onnx";
    vector<string> class_nums = {"face", "bicycle","car", "motorcycle", "airplane", "bus", "train"};

    int blur_rate = 30;
    int progress_bar = 0;

    process_video(model_path, videoFile.toStdString(), outputFilePath.toStdString(), class_nums, blur_rate, progress_bar);
}


void MainWindow::processRTPVideoButton() {
    qDebug() << "processVideoButton pushed";

    // выбор модели
    QString modelName = QFileDialog::getOpenFileName(
                this,
                tr("Выбор модели для обработки"),
                QString(),
                tr("ONNX Models (*.onnx)")
    );
    if (modelName.isEmpty()){
        qDebug() << "Не выбрана модель";
        return;
    }

    QString outputFilePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Processed Video"),
            QString(),
            tr("Video Files (*.mp4 *.avi *.mkv)")
        );
        if (outputFilePath.isEmpty()) {
            qDebug() << "Не указано место сохранения";
            return;
        }

    QString className = ui->comboBox->currentText();
    if (className.isEmpty()){
        qDebug() << "Не выбран класс";
        return;
    }

    qDebug() << "аут" << outputFilePath;
    qDebug() << "модель" << modelName;
    qDebug() << "класс" << className;

    int blurRate = blurValue;


    classesVector.clear();
    blurVector.clear();
    classesVector.push_back(className.toStdString());
    blurVector.push_back(blurRate);

    string model_path = "../models/yolov10n-face.onnx";
    vector<string> class_nums = {"face", "bicycle","car", "motorcycle", "airplane", "bus", "train"};

    int blur_rate = blurValue;

    process_rtp(model_path, outputFilePath.toStdString(), class_nums, blur_rate);
}

void MainWindow::openVideoWindow() {
    if (!videoWindow) {
        videoWindow = new VideoWindow(this);
    }
    videoWindow->show();
    videoWindow->raise();
    this->hide();
}

void MainWindow::updateVideoLabel(const QImage& frame) {
    ui->label_4->setPixmap(QPixmap::fromImage(frame));
}


//PROCESS VIDEO
int MainWindow::process_video(string model_path, string path_to_video, string path_to_save, vector<string> class_nums, int blur_rate, int& progress_bar) {
    Mat frame;
    VideoCapture cap;
    bool use_cuda = false;
    Size size(640,640);
    Size size2(320,320);

    Array input_data(640 * 640 * 3);
    Shape input_shape = {1, 3, 640, 640};
    int apiID = cv::CAP_ANY;

     VideoWriter writer;
    int codec = VideoWriter::fourcc('a', 'v', 'c', '1');

    cap.open(path_to_video);

    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);

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

    for (;;) {
        success = cap.read(frame);


        if (!success || frame.empty() || isStoped) {
            cout << "Processed " << total_frames << " of " << total_frames << " frames 100%" << endl;
            progress_bar = 100;
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
                        GaussianBlur(roi_img, blurred, Size(45, 45), blur_rate);

                        blurred.copyTo(frame(roi));
                    }
                }
            }
        }

        writer.write(frame);
        frame_count++;

        if (frame_count % 15 == 0) {
            progress_bar = (frame_count * 100) / total_frames;

            cout << "Processed " << frame_count << " of " << total_frames << " frames " << progress_bar << "%" << endl;
        }

        cv::resize(frame, frame, size2);
        QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
        updateVideoLabel(qimg);

        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        if (waitKey(5) >= 0)
            break;
    }

    cout << "Write complete !" << endl;
    cap.release();
    writer.release();

    return 0;
}
//PROCESS RTP
int MainWindow::process_rtp(string model_path, string path_to_save, vector<string> class_nums, int blur_rate) {
    Mat frame;
    VideoCapture cap;
    bool use_cuda = false;
    Size size(640,640);
    Size size2(480,480);

    Array input_data(640 * 640 * 3);
    Shape input_shape = {1, 3, 640, 640};
    int apiID = cv::CAP_ANY;

    VideoWriter writer;
    int codec = VideoWriter::fourcc('a', 'v', 'c', '1');

    int deviceID = 0;
    cap.open(deviceID, apiID);

    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);

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

    for (;;) {
        success = cap.read(frame);

        if (!success || frame.empty()  || isStoped) {
            cout << "Processed " << total_frames << " of " << total_frames << " frames 100%" << endl;
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
                        GaussianBlur(roi_img, blurred, Size(45, 45), blur_rate);

                        blurred.copyTo(frame(roi));
                    }
                }
            }
        }

        writer.write(frame);
        frame_count++;

        cv::resize(frame, frame, size2);
        QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
        updateVideoLabel(qimg);

        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        if (waitKey(5) >= 0)
            break;
    }

    cout << "Write complete !" << endl;
    cap.release();
    writer.release();

    return 0;
}


void MainWindow::stop_all(){
    isStoped = true;
    ui->label_4->clear();
}

void MainWindow::resume(){
    isStoped = false;

}

void MainWindow::blur_slider(int value) {
    ui->label_5->setText(QString::number(value));
    blurValue = value;
}



