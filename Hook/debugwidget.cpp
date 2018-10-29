#include "debugwidget.h"

#include <QTextEdit>

DebugWidget::DebugWidget()
{
    messageTextEdit = new QTextEdit;

    setCentralWidget(messageTextEdit);
}

void DebugWidget::MessageHandle(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        messageTextEdit->append(QString("Debug: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    case QtInfoMsg:
        messageTextEdit->append(QString("Info: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    case QtWarningMsg:
        messageTextEdit->append(QString("Warning: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    case QtCriticalMsg:
        messageTextEdit->append(QString("Critical: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    case QtFatalMsg:
        messageTextEdit->append(QString("Fatal: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        abort();
    }
}
