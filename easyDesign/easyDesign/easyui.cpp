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
    pic.load(p);
    pic = pic.scaled(w,h);
    setPixmap(pic);


    easymode->pixmapChange(pic);

}
void easyUI :: setButtonAction(const char* mode, bool check, QString tPixmap)
{
    buttonActionMode = QString(mode);
    buttonActionCheck = check;
    this->tPixmap = QPixmap(tPixmap).scaled(w,h);
}

bool easyUI :: eventFilter(QObject *o,QEvent *e)
{
    if (o == this)
    {
        if(e->type() == QEvent::Enter)
        {
            easymode->modecheck(buttonActionMode, 1, w, h, x, y, tPixmap);
            enter = true;
        }
        if(e->type() == QEvent::Leave)
        {
            easymode->modecheck(buttonActionMode, 0, w, h, x, y, tPixmap);
            enter = false;
        }

    }


    return QLabel::eventFilter(o, e);
}
void easyUI :: changeAction(bool check, int time, const char *pic)
{
    easymode->changeAction(check, time, QPixmap(QString(pic)).scaled(w, h));
}

void easyUI :: mousePressEvent(QMouseEvent *e)
{
    pressed   = true;
    pressedX = e->x();
    pressedY = e->y();
}

void easyUI :: mouseReleaseEvent(QMouseEvent *e)
{
    if(pressed && enter)
        emit clicked();
}

void easyUI :: mouseMoveEvent(QMouseEvent *e)
{
    enter = false;
}

easyUI :: ~easyUI()
{

}
