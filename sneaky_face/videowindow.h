#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QDialog>
#include <QCloseEvent>

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

private:
    Ui::VideoWindow *ui;
};

#endif // VIDEOWINDOW_H
