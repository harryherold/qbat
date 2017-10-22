#include "battery_window.h"
#include <utils.h>

#include <QDebug>

BatteryWindow::BatteryWindow()
{
    QDBusConnection system_bus = QDBusConnection::systemBus ();

    m_upower = new UPower("org.freedesktop.UPower",
                          "/org/freedesktop/UPower",
                          system_bus);

    bool ret = system_bus.connect("org.freedesktop.UPower",
                                  "/org/freedesktop/UPower",
                                  "org.freedesktop.DBus.Properties",
                                  "PropertiesChanged",
                                  this,
                                  SLOT(updateUPowerProperties(QString, QMap<QString, QVariant>,QStringList)));
    if(! ret)
    {
        qFatal("Cannot connect to upower dbus signal");
    }

    m_timer = new QTimer(this);

    initializePowerDevices();
}

BatteryWindow::~BatteryWindow()
{
    for(BatteryIcon * battery: m_batteryIcons)
    {
        delete battery;
    }
}

void BatteryWindow::initializePowerDevices()
{
    QDBusPendingReply<QList<PowerDevicePath>> reply = m_upower->EnumerateDevices ();
    reply.waitForFinished();

    if(! reply.isValid())
    {
        qFatal("Quering power devices failed");
    }

    for(const PowerDevicePath & dp: reply.value())
    {
        UPowerDevice * dev = new UPowerDevice("org.freedesktop.UPower",
                                              dp.path(),
                                              QDBusConnection::systemBus (),
                                              this);
        if(dev->type() == 2 && dev->nativePath().contains("BAT"))
        {
            qDebug() << "Add device " << dev->nativePath();
            BatteryIcon * battery = new BatteryIcon(dev, this);
            connect(m_timer, SIGNAL(timeout()), battery, SLOT(update()));
            connect(this, SIGNAL(powerStateChanged()), battery, SLOT(update()));
            m_batteryIcons.append(battery);
        }
        else
        {
            delete dev;
        }
    }
    m_timer->start(5000);
}

void BatteryWindow::updateUPowerProperties(QString, QMap<QString, QVariant> dict, QStringList)
{
    if(dict.contains(QString("OnBattery")))
    {
        qDebug() << "[BatteryWindow] : Updated upower properties";
        emit powerStateChanged();
    }
}
