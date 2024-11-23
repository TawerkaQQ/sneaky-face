#include "videowindow.h"
#include "ui_videowindow.h"
#include "mainwindow.h"

VideoWindow::VideoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VideoWindow)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, &VideoWindow::close);
}

VideoWindow::~VideoWindow()
{
    delete ui;
}

void VideoWindow::closeEvent(QCloseEvent *event)
{
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent());
    if (mainWindow) {
        mainWindow->show();
    }
    event->accept();
}
