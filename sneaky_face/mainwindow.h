#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videowindow.h"
#include "face_detect.h"
#include <QMainWindow>
#include <QComboBox>
#include <vector>
#include <string>

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

private:
    Ui::MainWindow *ui;
    VideoWindow *videoWindow;
    std::vector<std::string> classesVector;
    std::vector<int> blurVector;
};

#endif // MAINWINDOW_H
