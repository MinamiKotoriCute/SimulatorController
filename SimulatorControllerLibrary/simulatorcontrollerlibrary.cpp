#include "simulatorcontrollerlibrary.h"

#include "simulatorcontrollerlibraryprivate.h"

SimulatorControllerLibrary::SimulatorControllerLibrary()
{
    d = new SimulatorControllerLibraryPrivate;
    connect(d, &SimulatorControllerLibraryPrivate::getScreenshotFinish, this, &SimulatorControllerLibrary::getScreenshotFinish);
}

bool SimulatorControllerLibrary::getScreenshot()
{
    return d->getScreenshot();
}

bool SimulatorControllerLibrary::mouseLeftDown(int x, int y)
{
    return d->mouseLeftDown(x, y);
}

bool SimulatorControllerLibrary::mouseLeftMove(int x, int y)
{
    return d->mouseLeftMove(x, y);
}

bool SimulatorControllerLibrary::mouseLeftUp(int x, int y)
{
    return d->mouseLeftUp(x, y);
}

SimulatorControllerLibrary &getInstance()
{
    static SimulatorControllerLibrary object;
    return object;
}
