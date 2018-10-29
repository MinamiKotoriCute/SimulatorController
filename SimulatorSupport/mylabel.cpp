#include "mylabel.h"

#include <QMouseEvent>
#include <QTimer>
#include <QThread>

#include "../SimulatorControllerLibrary/simulatorcontrollerlibrary.h"
#pragma comment(lib, "../build-SimulatorControllerLibrary-Desktop_Qt_5_11_2_MSVC2017_64bit-Debug/debug/SimulatorControllerLibrary.lib")

#define RETRY_GETSCREENSHOT_TIME 100

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    scl = new SimulatorControllerLibrary;

    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, [=]{
        if(scl->getScreenshot())
            timer->stop();
    });

    connect(scl, &SimulatorControllerLibrary::getScreenshotFinish, [=](QImage img){
        setPixmap(QPixmap::fromImage(img));
        if(scl->getScreenshot() == false)
            timer->start(RETRY_GETSCREENSHOT_TIME);
    });

    timer->start(RETRY_GETSCREENSHOT_TIME);
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    scl->mouseLeftDown(event->x(), event->y());
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    scl->mouseLeftMove(event->x(), event->y());
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    scl->mouseLeftUp(event->x(), event->y());
}
