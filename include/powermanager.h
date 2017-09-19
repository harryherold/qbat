#pragma once

#include <QVector>
#include <QtDBus>
#include <QString>
#include <QDebug>

using PowerDevicePath = QDBusObjectPath;

class PowerManagement : public QObject
{
    Q_OBJECT

public:
    PowerManagement(QObject* parent=NULL);

    virtual ~PowerManagement();

    static QList<PowerDevicePath> queryBatteries();
};