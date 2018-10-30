#ifndef EASYMODE_H
#define EASYMODE_H
#include <QLabel>
#include <QWidget>

class easyMode : public QLabel
{
    Q_OBJECT

    public:
        easyMode(QLabel *parent);
        ~easyMode();

        void modecheck(QString mode, bool check = true, int w = 0, int h = 0, int x = 0, int y = 0,
                       QPixmap *tPixmap = 0, QPixmap **cPixmap = 0, int time = 0);

        void pixmapChange(QPixmap *p);

        void scaled(bool check, int w, int h);

        QPixmap *pixmap;

    private:
        QLabel *modeparent;

};


#endif // EASYMODE_H
