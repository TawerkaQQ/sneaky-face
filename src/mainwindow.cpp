#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videowindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openVideo);
    connect(ui->pushButton2, &QPushButton::clicked, this, &MainWindow::openProcessor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openVideo() {
    QString filePath = QFileDialog::getOpenFileName(this, "Video to play", "", "Video Files (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << "file selected:" << filePath;
        VideoWindow *videoWindow = new VideoWindow(filePath, this);
        videoWindow->show();
        ui->pushButton->hide();
    } else {
        qDebug() << "file not selected";
    }
}

void MainWindow::openProcessor() {
    QString filePath = QFileDialog::getOpenFileName(this, "Video for processing", "", "Video Files (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << "file selected:" << filePath;
        processVideo(filePath);
    }
}

void processVideo(QString filePath){
    qDebug() << "в функции-заглушке" << filePath;
}
