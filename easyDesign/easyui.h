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

        QPixmap pic, tPixmap;
        bool buttonActionCheck  = false;
        QString buttonActionMode;

        void init(int w,int h,int x,int y, QString p);
        void setButtonAction(const char* mode, bool check = true, QString tPixmap = 0);
        void changeAction(bool check, int time = 0, const char *pic = 0);
        void moveAction(bool check, int time = 0, int x = 0, int y = 0, QString mode = 0);
    private:

        easyMode *easymode;

        bool pressed = false;
        bool enter = false;
        int pressedX,pressedY;

        int w,h,x,y;

    protected:
        bool eventFilter(QObject *o, QEvent *e);
        void mouseReleaseEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
    signals:
        void clicked();

};







#endif // EASYUI_H
