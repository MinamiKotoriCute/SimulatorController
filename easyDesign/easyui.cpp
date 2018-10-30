#include "easyui.h"


easyUI :: easyUI(QWidget *parent):
    QLabel(parent),
    easymode(new easyMode(this))

{
    installEventFilter(this);

}


void easyUI :: init(int w, int h, int x, int y,QString p)
{
    buttonActionMode = QString("scaled");

    this->w = w; this->h = h; this->x = x; this->y = y;
    resize(w, h);
    move(x, y);
    pic = new QPixmap;
    pic->load(p);
    *pic = pic->scaled(w,h);
    setPixmap(*pic);
    tPixmap = new QPixmap;

    easymode->pixmapChange(pic);

}
void easyUI :: setButtonAction(const char* mode, bool check)
{
    buttonActionMode = QString(mode);
    buttonActionCheck = check;
}

bool easyUI :: eventFilter(QObject *o,QEvent *e)
{
    if (o == this)
    {
        if(e->type() == QEvent::Enter)
            easymode->modecheck(QString("scaled"), 1, w, h, x, y, tPixmap);
        if(e->type() == QEvent::Leave)
            easymode->modecheck(QString("scaled"), 0, w, h, x, y, tPixmap);
    }


    return QLabel::eventFilter(o, e);
}
void easyUI :: mousePressEvent(QMouseEvent *e)
{
    pressed   = true;
    pressedX = e->x();
    pressedY = e->y();
}

void easyUI :: mouseReleaseEvent(QMouseEvent *e)
{

}



easyUI :: ~easyUI()
{

}
