#include "client.h"

#include <QTcpSocket>
#include <QTimer>

#define HOST_NAME "127.0.0.1"
#define HOST_PORT 9633

#define RECONNECT_TIME 1000

struct CS_Header
{
    unsigned int size;
    unsigned int messageType;
};

enum Client2ServerHeader
{
    ResponseScreenshot,
};

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket;
    connect(socket, &QTcpSocket::readyRead, this, &Client::apiHandle);
    connect(socket, &QTcpSocket::connected, []{
        qInfo("connected");
    });
    connect(socket, &QTcpSocket::disconnected, [this]{
        socket->close();
        qInfo("disconnected");
        connectTimer->start(RECONNECT_TIME);
    });

    connectTimer = new QTimer;
    connect(connectTimer, &QTimer::timeout, this, &Client::connectToHost);
    connectTimer->start(RECONNECT_TIME);
}

void Client::responseScreenshot(QImage img)
{
    qInfo("responseScreenshot");

    struct CS_ResponseScreenshot : CS_Header
    {
        int width;
        int height;
        //unsigned char *imageBits;
    };

    CS_ResponseScreenshot packet;
    packet.messageType = ResponseScreenshot;
    packet.width = img.width();
    packet.height = img.height();
    //packet.imageBits = img.bits();

    QByteArray binary = QByteArray::fromRawData((const char*)&packet, sizeof(packet));
    binary += QByteArray::fromRawData((const char*)img.bits(), img.sizeInBytes());
    qDebug("size:%d", img.sizeInBytes());

    (*(unsigned int*)binary.data()) = binary.size();

    socket->write(binary);
}

void Client::connectToHost()
{
    if(socket->isOpen())
    {
        qWarning("socket already open");
        return;
    }

    socket->connectToHost(HOST_NAME, HOST_PORT);
    if(socket->waitForConnected(1))
        connectTimer->stop();
    else
        socket->close();
}

void Client::apiHandle()
{
    enum Server2ClientHeader
    {
        RequestScreenshot,
    };

    auto packet = socket->readAll();
    if(packet.size() == 0)
    {
        qWarning("read packet size = 0");
        return;
    }

    qInfo("receive %hhu", packet[0].operator char());
    switch (packet[0]) {
    case RequestScreenshot:
        emit requestScreenshot();
        break;
    }
}
