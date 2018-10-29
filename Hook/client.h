#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QImage>

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void responseScreenshot(QImage img);

signals:
    void requestScreenshot();

public slots:
    void connectToHost();

private slots:
    void apiHandle();

private:
    QTimer *connectTimer;
    QTcpSocket *socket;
};

#endif // CLIENT_H
