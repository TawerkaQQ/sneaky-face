#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>

namespace Ui {
class VideoWindow;
}

class VideoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VideoWindow(QWidget *parent = nullptr);
    ~VideoWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_openButton_clicked();
    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_errorOccurred(QMediaPlayer::Error error);

private:
    Ui::VideoWindow *ui;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
};

#endif // VIDEOWINDOW_H
