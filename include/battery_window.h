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
    void update(void);
    void updateUPowerProperties(QString, QMap<QString, QVariant>,QStringList);

signals:
    void powerStateChanged();

private:
    QTimer * m_timer;
    UPower * m_upower;
    QList<BatteryIcon *> m_batteryIcons;

    QSystemTrayIcon * m_trayIcon;
    QRectF m_progressRect;
    QRectF m_batteryRect;
    QList<UPowerDevice *> m_devices;
    void initializePowerDevices();
    void drawIcon(double percentage, BatteryState state);
    QColor getColor(double percentage);
    double getAccumulatedPercentage(void);
    double getAccumulatedTime(void);
};

#endif // BATTERY_WINDOW_H