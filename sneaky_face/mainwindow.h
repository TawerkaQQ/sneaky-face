#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videowindow.h"
#include "face_detect.h"
#include <QMainWindow>
#include <QComboBox>
#include <vector>
#include <string>
#include <QImage>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void processVideoButton();
    void openVideoWindow();
    void processRTPVideoButton();
    void stop_all();
    void resume();
    void blur_slider(int value);

private:
    Ui::MainWindow *ui;
    VideoWindow *videoWindow;
    std::vector<std::string> classesVector;
    std::vector<int> blurVector;
    bool isStoped = false;
    int blurValue;
    int thisProgressBar = 0;
//    vector<string>;


    void updateVideoLabel(const QImage& frame);
    int process_video(std::string model_path, std::string path_to_video, std::string path_to_save, std::vector<std::string> class_nums, int blur_rate, int& progress_bar);
    int process_rtp(std::string model_path, std::string path_to_save, std::vector<std::string> class_nums, int blur_rate);
};

#endif // MAINWINDOW_H
