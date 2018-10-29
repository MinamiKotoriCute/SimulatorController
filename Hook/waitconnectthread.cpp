#include "waitconnectthread.h"

#include <QTcpSocket>

#define HOST_NAME "127.0.0.1"
#define HOST_PORT 9633

WaitConnectThread::WaitConnectThread(QTcpSocket *socket, QObject *parent) : QThread(parent), socket(socket)
{

}

void WaitConnectThread::run()
{
    qDebug("run");
    while (true) {
        socket->connectToHost(HOST_NAME, HOST_PORT);
        if(socket->waitForConnected(1000))
            break;
    }
    qDebug("run exit");
}
