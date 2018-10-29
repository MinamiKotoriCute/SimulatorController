#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class QMouseEvent;
class SimulatorControllerLibrary;

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    SimulatorControllerLibrary *scl;
};

#endif // MYLABEL_H
