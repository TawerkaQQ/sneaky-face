#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>

class VideoWindow : public QWidget {
    Q_OBJECT

public:
    VideoWindow(const QString &filePath, QWidget *parent = nullptr);
    ~VideoWindow();

private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
};

#endif // VIDEOWINDOW_H
