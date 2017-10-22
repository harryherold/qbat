#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include "battery_window.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    #ifndef QT_NO_DEBUG
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtInfoMsg:
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            abort();
        }
    #endif
}

int main (int argc, char **argv)
{
    qInstallMessageHandler(myMessageOutput);
    QApplication app (argc, argv);

    BatteryWindow bat;

    return app.exec ();
}
