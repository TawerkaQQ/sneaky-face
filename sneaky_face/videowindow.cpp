#include "videowindow.h"
#include "ui_videowindow.h"
#include "mainwindow.h"
#include <QDebug>

VideoWindow::VideoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VideoWindow)
{
    ui->setupUi(this);

    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);

    mediaPlayer->setVideoOutput(videoWidget);

    ui->verticalLayout->addWidget(videoWidget);

    // Use Qt::UniqueConnection to prevent multiple connections
    connect(ui->playButton, &QPushButton::clicked, this, &VideoWindow::on_playButton_clicked, Qt::UniqueConnection);
    connect(ui->pauseButton, &QPushButton::clicked, this, &VideoWindow::on_pauseButton_clicked, Qt::UniqueConnection);
    connect(ui->openButton, &QPushButton::clicked, this, &VideoWindow::on_openButton_clicked, Qt::UniqueConnection);
    connect(ui->backButton, &QPushButton::clicked, this, &VideoWindow::close, Qt::UniqueConnection);

    // Connect media status and error signals
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &VideoWindow::on_mediaStatusChanged);
    connect(mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &VideoWindow::on_errorOccurred);
}

VideoWindow::~VideoWindow()
{
    delete ui;
    delete mediaPlayer;
    delete videoWidget;
}

void VideoWindow::closeEvent(QCloseEvent *event)
{
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent());
    if (mainWindow) {
        mainWindow->show();
    }
    event->accept();
}

void VideoWindow::on_playButton_clicked()
{
    mediaPlayer->play();
}

void VideoWindow::on_pauseButton_clicked()
{
    mediaPlayer->pause();
}

void VideoWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files (*.mp4 *.avi *.mkv)"));
    if (!fileName.isEmpty()) {
        mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
    }
}

void VideoWindow::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        mediaPlayer->play();
    }
}

void VideoWindow::on_errorOccurred(QMediaPlayer::Error error)
{
    qDebug() << "Media Player Error:" << error;
}
