#ifndef POWERMANAGEMENT_H
#define POWERMANAGEMENT_H

#include <QDebug>
#include <QString>
#include <QtDBus>

#include <upower.h>
#include <upower_device.h>

using PowerDevicePath = QDBusObjectPath;

enum class DeviceTypes
{
    UNKOWN = 0,
    LINEPOWER = 1,
    BATTERY = 2,
    UPS = 3,
    MONITOR = 4,
    MOUSE = 5,
    KEYBOARD = 6,
    PDA = 7,
    PHONE = 8
};

class PowerManagement : public QObject
{
    Q_OBJECT
    using UPowerDevice = OrgFreedesktopUPowerDeviceInterface;

    public:
    PowerManagement (QObject *parent = NULL);
    virtual ~PowerManagement ();

    uint getPowerDeviceCount ()
    {
        return m_upower_devices.count ();
    }

    private:
    OrgFreedesktopUPowerInterface m_upower;
    QList<UPowerDevice *> m_upower_devices;

    void initializePowerDevices (void);
};

#endif // POWERMANAGEMENT_H