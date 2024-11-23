/********************************************************************************
** Form generated from reading UI file 'videowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOWINDOW_H
#define UI_VIDEOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoWindow
{
public:
    QPushButton *backButton;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *openButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *VideoWindow)
    {
        if (VideoWindow->objectName().isEmpty())
            VideoWindow->setObjectName(QString::fromUtf8("VideoWindow"));
        VideoWindow->resize(986, 562);
        backButton = new QPushButton(VideoWindow);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(890, 10, 89, 25));
        playButton = new QPushButton(VideoWindow);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(20, 430, 89, 25));
        pauseButton = new QPushButton(VideoWindow);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setGeometry(QRect(20, 460, 89, 25));
        openButton = new QPushButton(VideoWindow);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(20, 490, 89, 25));
        verticalLayoutWidget = new QWidget(VideoWindow);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 871, 411));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(VideoWindow);

        QMetaObject::connectSlotsByName(VideoWindow);
    } // setupUi

    void retranslateUi(QWidget *VideoWindow)
    {
        VideoWindow->setWindowTitle(QCoreApplication::translate("VideoWindow", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("VideoWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        playButton->setText(QCoreApplication::translate("VideoWindow", "play", nullptr));
        pauseButton->setText(QCoreApplication::translate("VideoWindow", "pause", nullptr));
        openButton->setText(QCoreApplication::translate("VideoWindow", "open video", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoWindow: public Ui_VideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOWINDOW_H
