#include "easymode.h"

easyMode :: easyMode(QLabel *parent)
{
    modeparent = parent;
    caTimer = new QTimer(this);
    mvTimer = new QTimer(this);
    connect(caTimer,&QTimer::timeout,[=]{
        if(!caCheck)
        {
            modeparent->setPixmap(cPixmap);
            caCheck = true;
        }
        else
        {
            modeparent->setPixmap(pixmap);
            caCheck = false;
        }
    });
}


void easyMode :: modecheck(QString mode, bool check, int w, int h, int x, int y, QPixmap tPixmap, int time)
{
    if(mode == QString("scaled"))
        scaled(check, w, h);
    else if(mode == QString("conversion"))
        conversion(check, tPixmap);
}


void easyMode :: pixmapChange(QPixmap p)
{
    pixmap = p;
}

void easyMode :: scaled(bool check, int w, int h)
{
    if(check)
    {
        modeparent->resize(w+30, h+30);
        modeparent->setPixmap(pixmap.scaled(w+30, h+30));
    }
    else
    {
        modeparent->resize(w, h);
        modeparent->setPixmap(pixmap.scaled(w, h));
    }

}

void easyMode :: conversion(bool check, QPixmap tPixmap)
{
    if(check)
        modeparent->setPixmap(tPixmap);
    else
        modeparent->setPixmap(pixmap);
}

void easyMode :: changeAction(bool check, int time, QPixmap cPixmap)
{
    if(check)
    {
        this->cPixmap = cPixmap;
        caTimer->start(time);
    }
    else
        caTimer->stop();
}


easyMode :: ~easyMode()
{

}
