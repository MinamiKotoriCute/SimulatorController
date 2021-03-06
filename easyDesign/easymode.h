#ifndef EASYMODE_H
#define EASYMODE_H
#include <QLabel>
#include <QWidget>
#include <QTimer>

class easyMode : public QLabel
{
    Q_OBJECT

    public:
        easyMode(QLabel *parent);
        ~easyMode();

        void modecheck(QString mode, bool check = true, int w = 0, int h = 0, int x = 0, int y = 0,
                       QPixmap tPixmap = QPixmap(), int time = 0);

        void pixmapChange(QPixmap p);

        void scaled(bool check, int w, int h);
        void conversion(bool check, QPixmap tPixmap);
        void changeAction(bool check, int time, QPixmap cPixmap);
        void moveAction(bool check, int time, int x, int y, QString mode);
        bool caCheck = false;
        bool moveLock = false;
        int moveGrid = 0;
        int *spaceX, *spaceY;
        int mvTemp = 0;

        QPixmap pixmap,cPixmap;
        QTimer *caTimer, *mvTimer;

    private:
        QLabel *modeparent;

};


#endif // EASYMODE_H
