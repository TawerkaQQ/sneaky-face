#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videowindow.h"
#include <QMainWindow>
#include <QComboBox>

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
};

#endif // MAINWINDOW_H
