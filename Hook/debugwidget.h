#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QMainWindow>

class QTextEdit;

class DebugWidget : public QMainWindow
{
    Q_OBJECT
public:
    DebugWidget();
    void MessageHandle(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:

public slots:

private:


    QTextEdit *messageTextEdit;
};

#endif // DEBUGWIDGET_H
