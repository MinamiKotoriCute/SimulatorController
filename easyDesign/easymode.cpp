#include "easymode.h"

easyMode :: easyMode(QLabel *parent)
{
    modeparent = parent;
    pixmap = new QPixmap;
}


void easyMode :: modecheck(QString mode, bool check, int w, int h, int x, int y, QPixmap *tPixmap, QPixmap **cPixmap, int time)
{
    if(mode == QString("scaled"))
        scaled(check, w, h);
}


void easyMode :: pixmapChange(QPixmap *p)
{
    pixmap = p;
}

void easyMode :: scaled(bool check, int w, int h)
{
    if(check)
    {
        modeparent->resize(w+30, h+30);
        modeparent->setPixmap(pixmap->scaled(w+30, h+30));
    }
    else
    {
        modeparent->resize(w, h);
        modeparent->setPixmap(pixmap->scaled(w, h));
    }

}



easyMode :: ~easyMode()
{

}
