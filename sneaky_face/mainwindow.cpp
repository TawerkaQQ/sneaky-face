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

    // Подключаем сигнал нажатия кнопки к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openVideo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openVideo() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите видео", "", "Video Files (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << "выбран файл:" << filePath;
        VideoWindow *videoWindow = new VideoWindow(filePath, this);
        videoWindow->show();
        ui->pushButton->hide();
    } else {
        qDebug() << "файл не выбран";
    }
}
