#ifndef BATTERY_WINDOW_H
#define BATTERY_WINDOW_H

#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QTimer>

#include <upower.h>
#include <upower_device.h>

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
    void quit();
    void updateIcon();

protected:
    void closeEvent(QCloseEvent *event);

private:
    QSystemTrayIcon * m_trayIcon;
    QMenu * m_trayIconMenu;
    QAction * m_quitAction;
    QTimer * m_timer;
    UPower * m_upower;
    QList<UPowerDevice *> m_upower_devices;

    // TODO should be a constexpr
    const uint m_powerSteps = 5;
    const char * m_iconPathTemplate = "/home/cherold/cpp-workspace/qbat/images/%1-%2-icon.png";

    void createTrayIcon();
    void createActions();

    void initializePowerDevices();
    void initializeIcons();

    uint getBatteryLevel();
};

#endif // BATTERY_WINDOW_H