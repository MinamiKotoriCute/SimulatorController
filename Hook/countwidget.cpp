#include "countwidget.h"

#include <QTextEdit>
#include <QHBoxLayout>
#include <QApplication>

CountWidget::CountWidget(QWidget *parent) : QWidget(parent)
{
    e = new QTextEdit;

    QHBoxLayout *hb = new QHBoxLayout;
    hb->addWidget(e);

    setLayout(hb);
}

void CountWidget::add(QString name)
{
    ++count[name];

    QString text;
    for(auto it = count.cbegin();it!=count.cend();++it)
    {
        const auto &name = it.key();
        const auto &count = it.value();

        text += QString("%1 = %2\n").arg(name).arg(count);
    }

    e->setText(text);

    show();

    for(unsigned int i=0;i<10;++i)
        qApp->processEvents();
}
