#include "videowindow.h"
#include <QUrl>
#include <QDebug>

VideoWindow::VideoWindow(const QString &filePath, QWidget *parent)
    : QWidget(parent)
    , player(new QMediaPlayer(this))
    , videoWidget(new QVideoWidget(this))
    , playButton(new QPushButton("плей", this))
    , pauseButton(new QPushButton("пауза", this))
    , openButton(new QPushButton("новое видео", this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(openButton);

    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile(filePath));

    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, [this](QMediaPlayer::Error error) {
        qDebug() << "ошибка воспроизведения:" << player->errorString();
    });
    connect(playButton, &QPushButton::clicked, this, &VideoWindow::play);
    connect(pauseButton, &QPushButton::clicked, this, &VideoWindow::pause);
    connect(openButton, &QPushButton::clicked, this, &VideoWindow::openNewVideo);

    this->resize(800, 600);

    player->play();
}

VideoWindow::~VideoWindow() {
    delete player;
    delete videoWidget;
}

void VideoWindow::play() {
    player->play();
}

void VideoWindow::pause() {
    player->pause();
}

void VideoWindow::openNewVideo() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите видео", "", "Video Files (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << "Выбран файл:" << filePath;
        player->setMedia(QUrl::fromLocalFile(filePath));
        player->play();
    } else {
        qDebug() << "Файл не выбран";
    }
}
