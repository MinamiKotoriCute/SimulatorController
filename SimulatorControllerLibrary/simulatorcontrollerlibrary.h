#ifndef SIMULATORCONTROLLERLIBRARY_H
#define SIMULATORCONTROLLERLIBRARY_H

#include "simulatorcontrollerlibrary_global.h"

#include <QObject>
#include <QImage>

class SIMULATORCONTROLLERLIBRARYSHARED_EXPORT SimulatorControllerLibrary : public QObject
{
    Q_OBJECT
public:
    SimulatorControllerLibrary();

    bool getScreenshot();

    bool mouseLeftDown(int x, int y);
    bool mouseLeftMove(int x, int y);
    bool mouseLeftUp(int x, int y);

signals:
    void getScreenshotFinish(QImage);

private:
    class SimulatorControllerLibraryPrivate *d;
};

#endif // SIMULATORCONTROLLERLIBRARY_H
