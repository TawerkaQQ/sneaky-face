#include "videowindow.h"
#include <QUrl>
#include <QDebug>

VideoWindow::VideoWindow(const QString &filePath, QWidget *parent)
    : QWidget(parent)
    , player(new QMediaPlayer(this))
    , videoWidget(new QVideoWidget(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);

    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile(filePath));

    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, [this](QMediaPlayer::Error error) {
        qDebug() << "Ошибка воспроизведения:" << player->errorString();
    });

    // Устанавливаем размер окна
    this->resize(800, 600);

    player->play();
}

VideoWindow::~VideoWindow() {
    delete player;
    delete videoWidget;
}
