#ifndef EASYUI_H
#define EASYUI_H

#include<QList>
#include<QLabel>
#include <QMouseEvent>
#include "easymode.h"

class easyUI : public QLabel
{
    Q_OBJECT

    public:
        easyUI(QWidget *parent = 0);
        ~easyUI();

        QPixmap *pic, *tPixmap;
        bool buttonActionCheck  = false;
        QString buttonActionMode;

        void init(int w,int h,int x,int y, QString p);
        void setButtonAction(const char* mode, bool check = true);
    private:

        easyMode *easymode;

        bool pressed = false;
        int pressedX,pressedY;

        int w,h,x,y;

    protected:
        bool eventFilter(QObject *o, QEvent *e);
        void mouseReleaseEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);


};







#endif // EASYUI_H
