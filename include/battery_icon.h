#ifndef BATTERY_ICON_H
#define BATTERY_ICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QPixmap>
#include <QPainter>
#include <utils.h>

#include <upower_device.h>

class BatteryIcon: public QObject
{
    Q_OBJECT

    using UPowerDevice = OrgFreedesktopUPowerDeviceInterface;

public:
    BatteryIcon(UPowerDevice * dev, QObject* parent = 0);
    virtual ~BatteryIcon();

public  slots:
    void update(void);
    void quit(void);

private:
    UPowerDevice * m_upowerDevice;
    QSystemTrayIcon * m_trayIcon;
    QMenu * m_trayIconMenu;
    QAction * m_quitAction;

    QPixmap * m_batteryPic;
    QPixmap * m_boltPic;
    QRectF m_progressRect;
    QRectF m_boltSourceRect;
    QRectF m_boltTargetRect;

    QColor getColor(double percentage);
};

#endif //BATTERY_ICON_H