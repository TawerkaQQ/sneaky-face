#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videowindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QWidget>

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
    QString filePath = QFileDialog::getOpenFileName(this, "видео для воспроизведения", "", "Video Files (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << "выбран файл:" << filePath;
        VideoWindow *videoWindow = new VideoWindow(filePath, this);
        videoWindow->show();
        ui->pushButton->hide();
    } else {
        qDebug() << "файл не выбран";
    }
}

void MainWindow::openProcessor() {
    QString filePath = QFileDialog::getOpenFileName(this, "видео для обработки", "", "Video Files (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << "выбран файл:" << filePath;
        processVideo(filePath);
    }
}

void processVideo(QString filePath){
    qDebug() << "в функции-заглушке" << filePath;
}
