#ifndef SIMULATORCONTROLLERLIBRARYPRIVATE_H
#define SIMULATORCONTROLLERLIBRARYPRIVATE_H

#include <QObject>
#include <QTcpServer>
#include <QImage>

#include <atlbase.h>
#include <Windows.h>

class SimulatorControllerLibraryPrivate : public QObject
{
    Q_OBJECT
public:
    explicit SimulatorControllerLibraryPrivate(QObject *parent = nullptr);

    bool getScreenshot();

    bool mouseLeftDown(int x, int y);
    bool mouseLeftMove(int x, int y);
    bool mouseLeftUp(int x, int y);
    void keyboardDown(char c);
    void keyboardUp(char c);

signals:
    void getScreenshotFinish(QImage);

public slots:

private slots:
    void newConnection();
    void readyRead();

private:
    HWND hwnd;
    QTcpSocket *socket = nullptr;
    QTcpServer *server;
    QByteArray binary;
};

#endif // SIMULATORCONTROLLERLIBRARYPRIVATE_H
