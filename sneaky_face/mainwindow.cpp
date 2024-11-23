#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "face_detect.h"
#include <QDebug>
#include <string>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , videoWindow(nullptr)
{
    ui->setupUi(this);
    //INPUT BUTTON
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::processVideoButton);

    std::vector<std::string> classes = getClassName();
    for (const std::string& class_name : classes) {
        ui->comboBox->addItem(QString::fromStdString(class_name));
    }

    std::vector<std::string> models = getModelName();
    for (const std::string& model_name : models) {
        ui->comboBox_2->addItem(QString::fromStdString(model_name));
    }

    //WATCH_VIDEO BUTTON
    connect(ui->pushButton2, &QPushButton::clicked, this, &MainWindow::openVideoWindow);

    // RTP_VIDEO_BUTTON
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::processRTPVideoButton);
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


    // success = process(modelName.toStdString(), videoFile.toStdString(), outputFilePath.toStdString(), classesVector, blurVector);

    string model_path = "../models/yolov10n-face.onnx";
    vector<string> class_nums = {"face", "bicycle","car", "motorcycle", "airplane", "bus", "train"};

    int blur_rate = 30;
    int progress_bar = 0;

    process_video(model_path, videoFile.toStdString(), outputFilePath.toStdString(), class_nums, blur_rate, progress_bar);
}

// RTP VIDEO_PROCESS
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

    int blurRate = 100;

    classesVector.clear();
    blurVector.clear();
    classesVector.push_back(className.toStdString());
    blurVector.push_back(blurRate);




    string model_path = "../models/yolov10n-face.onnx";
    vector<string> class_nums = {"face", "bicycle","car", "motorcycle", "airplane", "bus", "train"};

    int blur_rate = 30;

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
