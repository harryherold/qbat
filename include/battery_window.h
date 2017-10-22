#ifndef BATTERY_WINDOW_H
#define BATTERY_WINDOW_H

#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QTimer>

#include <upower.h>
#include <upower_device.h>
#include "battery_icon.h"

class BatteryWindow: public QObject
{
    Q_OBJECT

    using UPower = OrgFreedesktopUPowerInterface;
    using UPowerDevice = OrgFreedesktopUPowerDeviceInterface;
    using PowerDevicePath = QDBusObjectPath;

public:
    BatteryWindow();
    virtual ~BatteryWindow();

public slots:
    void updateUPowerProperties(QString, QMap<QString, QVariant>,QStringList);

signals:
    void powerStateChanged();

private:
    QTimer * m_timer;
    UPower * m_upower;
    QList<BatteryIcon *> m_batteryIcons;

    void initializePowerDevices();
};

#endif // BATTERY_WINDOW_H