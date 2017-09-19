#include "powermanager.h"

PowerManagement::PowerManagement(QObject* parent)
:QObject(parent)
{
}

PowerManagement::~PowerManagement()
{}

QList<PowerDevicePath> PowerManagement::queryBatteries()
{
    QDBusConnection system = QDBusConnection::systemBus();

    if (!system.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
    }

    QDBusMessage message = QDBusMessage::createMethodCall("org.freedesktop.UPower",
                                                          "/org/freedesktop/UPower",
                                                          "org.freedesktop.UPower",
                                                          "EnumerateDevices");

    QDBusPendingReply<QList<PowerDevicePath>> reply = QDBusConnection::systemBus().call(message);

    if (reply.isValid())
    {
        return reply.value();
    }
    else
    {
        qFatal("EnumerateDevices: result invalid");
    }
}