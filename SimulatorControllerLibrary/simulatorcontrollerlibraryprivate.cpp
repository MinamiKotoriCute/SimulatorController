#include "simulatorcontrollerlibraryprivate.h"

#include <QTcpServer>
#include <QTcpSocket>

#define HOST_NAME "127.0.0.1"
#define HOST_PORT 9633

SimulatorControllerLibraryPrivate::SimulatorControllerLibraryPrivate(QObject *parent) : QObject(parent)
{
    hwnd = 0;
    server = new QTcpServer;

    connect(server, &QTcpServer::newConnection, this, &SimulatorControllerLibraryPrivate::newConnection);

    server->listen(QHostAddress(HOST_NAME), HOST_PORT);

    findHwnd();
}

bool SimulatorControllerLibraryPrivate::getScreenshot()
{
    if(socket == nullptr || socket->state() != QAbstractSocket::ConnectedState)
    {
        return false;
    }

    QByteArray packet;
    packet.push_back((char)0);
    socket->write(packet);

    return true;
}

bool SimulatorControllerLibraryPrivate::mouseLeftDown(int x, int y)
{
    if(hwnd == 0) return false;
    LPARAM tLPar=(y<<16)+x; //滑鼠座標存在一個參數(Y<<16)+X
    SendMessageA(hwnd, WM_MOUSEMOVE, MK_LBUTTON, tLPar);
    SendMessageA(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, tLPar);
    return true;
}

bool SimulatorControllerLibraryPrivate::mouseLeftMove(int x, int y)
{
    if(hwnd == 0) return false;
    LPARAM tLPar=(y<<16)+x; //滑鼠座標存在一個參數(Y<<16)+X
    SendMessageA(hwnd, WM_MOUSEMOVE, MK_LBUTTON, tLPar);
    return true;
}

bool SimulatorControllerLibraryPrivate::mouseLeftUp(int x, int y)
{
    if(hwnd == 0) return false;
    LPARAM tLPar=(y<<16)+x; //滑鼠座標存在一個參數(Y<<16)+X
    SendMessageA(hwnd, WM_MOUSEMOVE, MK_LBUTTON, tLPar);
    SendMessageA(hwnd, WM_LBUTTONUP, 0, tLPar);
    return true;
}

void SimulatorControllerLibraryPrivate::newConnection()
{
    socket = server->nextPendingConnection();

    connect(socket, &QTcpSocket::readyRead, this, &SimulatorControllerLibraryPrivate::readyRead);

    findHwnd();
}

void SimulatorControllerLibraryPrivate::readyRead()
{
    binary += socket->readAll();
    //qDebug("%u : %u", *(unsigned int*)binary.data(), binary.size());
    if((*(unsigned int*)binary.data()) > binary.size())
        return;

    struct CS_ResponseScreenshot
    {
        unsigned int size;
        unsigned int messageType;
        int width;
        int height;
        //unsigned char *imageBits;
    };

    CS_ResponseScreenshot *d = (CS_ResponseScreenshot*)binary.data();
    //qDebug("messageType:%d width:%d, height:%d", d->messageType, d->width, d->height);
    if(d->messageType != 0)
        return;
    QImage img(d->width, d->height, QImage::Format_RGB888);
    memcpy(img.bits(), binary.data() + sizeof(CS_ResponseScreenshot), binary.size() - sizeof(CS_ResponseScreenshot));

    binary.clear();
    emit getScreenshotFinish(img);
}

void SimulatorControllerLibraryPrivate::findHwnd()
{
    HWND hwndTop = FindWindowA(nullptr, QStringLiteral("雷電模擬器").toLocal8Bit().data());
    if (hwndTop)
    {
        hwnd = GetWindow(hwndTop, GW_CHILD);
    }
    //qDebug("%u", (int)hwnd);
}
