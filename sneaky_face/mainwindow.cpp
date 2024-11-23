#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "face_detect.h"
#include <QDebug>

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

    //WATCH_VIDEO BUTTON
    connect(ui->pushButton2, &QPushButton::clicked, this, &MainWindow::openVideoWindow);
}

MainWindow::~MainWindow() {
    delete ui;
    delete videoWindow;
}

void MainWindow::processVideoButton() {
    qDebug() << "processVideoButton pushed";
}

void MainWindow::openVideoWindow() {
    if (!videoWindow) {
        videoWindow = new VideoWindow(this);
    }
    videoWindow->show();
    videoWindow->raise();
    this->hide();
}
