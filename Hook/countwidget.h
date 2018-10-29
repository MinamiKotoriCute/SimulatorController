#ifndef COUNTWIDGET_H
#define COUNTWIDGET_H

#include <QWidget>
#include <QMap>

class QTextEdit;

class CountWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CountWidget(QWidget *parent = nullptr);

    void add(QString name);

signals:

public slots:

private:
    QTextEdit *e;
    QMap<QString,int> count;
};

#endif // COUNTWIDGET_H
