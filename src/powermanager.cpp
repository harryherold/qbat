#include "powermanager.h"

PowerManagement::PowerManagement (QObject *parent)
: QObject (parent),
  m_upower ("org.freedesktop.UPower", "/org/freedesktop/UPower", QDBusConnection::systemBus ())
{
    if (!QDBusConnection::systemBus ().isConnected ())
    {
        qFatal ("Cannot connect to the D-Bus session bus.");
    }

    initializePowerDevices ();
}

PowerManagement::~PowerManagement ()
{
    for (UPowerDevice *dev : m_upower_devices)
    {
        delete dev;
    }
}

void PowerManagement::initializePowerDevices ()
{
    QDBusPendingReply<QList<PowerDevicePath>> reply = m_upower.EnumerateDevices ();
    reply.waitForFinished ();
    if (reply.isValid ())
    {
        for (int i = 0; i < reply.value ().count (); ++i)
        {
            UPowerDevice *dev = new OrgFreedesktopUPowerDeviceInterface ("org.freedesktop.UPower",
                                                                         reply.value ().at (i).path (),
                                                                         QDBusConnection::systemBus ());
            if (dev->type () == 2)
            {
                m_upower_devices.append (dev);
            }
        }
    }
}