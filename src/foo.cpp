#include "foo.h"

Foo::Foo (QObject * parent)
:QObject(parent)
{
    QDBusConnection dbus = QDBusConnection::systemBus ();
    // bool ret = dbus.connect("org.freedesktop.UPower",
    //                         "/org/freedesktop/UPower",
    //                         "org.freedesktop.DBus.Properties",
    //                         "PropertiesChanged",
    //                         this,
    //                         SLOT(updateProperties(QString, QMap<QString, QVariant>,QStringList)));
    // if (ret)
    //     qDebug () << "Connected";
    // else
    //     qDebug () << "Not connected";

    bool ret = dbus.connect("org.freedesktop.UPower",
                       "/org/freedesktop/UPower/devices/battery_BAT1",
                       "org.freedesktop.DBus.Properties",
                       "PropertiesChanged",
                       this,
                       SLOT(updateProperties(QString, QMap<QString, QVariant>,QStringList)));
    if (ret)
        qDebug () << "Connected";
    else
        qDebug () << "Not connected";
}

void Foo::updateProperties (QString s, QMap<QString, QVariant> dict, QStringList l)
{
    qDebug () << "update";
    if(dict.contains(QString("OnBattery")))
    {
        qDebug() << "BatteryOn ? " << dict["OnBattery"].toBool();
    }
    if(dict.contains(QString("Percentage")))
    {
        qDebug() << "Percentage : " << dict["Percentage"].toDouble();
    }
    qDebug() << s;
}