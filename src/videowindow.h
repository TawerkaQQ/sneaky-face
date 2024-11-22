#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>

class VideoWindow : public QWidget {
    Q_OBJECT

public:
    VideoWindow(const QString &filePath, QWidget *parent = nullptr);
    ~VideoWindow();

private  slots:
    void play();
    void pause();
    void openNewVideo();

private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *openButton;
};

#endif // VIDEOWINDOW_H
