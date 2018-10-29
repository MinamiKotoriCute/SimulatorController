#ifndef WAITCONNECTTHREAD_H
#define WAITCONNECTTHREAD_H

#include <QThread>

class QTcpSocket;

class WaitConnectThread : public QThread
{
    Q_OBJECT
public:
    explicit WaitConnectThread(QTcpSocket *socket, QObject *parent = nullptr);

signals:

public slots:

protected:
    void run() override;

private:
    QTcpSocket *socket;
};

#endif // WAITCONNECTTHREAD_H
