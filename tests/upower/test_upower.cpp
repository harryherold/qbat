#include "test_upower.h"
#include <unistd.h>



void TestUPower::query_device_paths ()
{
    QDBusConnection dbus = QDBusConnection::systemBus();
    UPower upower("org.freedesktop.UPower",
                  "/org/freedesktop/UPower",
                  dbus);

    QVERIFY( QDBusConnection::systemBus().isConnected() );

    QDBusPendingReply<QList<PowerDevicePath>> reply = upower.EnumerateDevices ();

    reply.waitForFinished();

    QVERIFY(reply.isValid ());

    QVERIFY(upower.onBattery() == false);

    //qDBusRegisterMetaType<QMap<QString, QVariant>>();

    bool ret = dbus.connect("org.freedesktop.UPower",
                 "/org/freedesktop/UPower",
                 "org.freedesktop.DBus.Properties",
                 "PropertiesChanged",
                 this,
                 SLOT(updateProperties(QString, QMap<QString, QVariant>,QStringList)));

    if(ret) qDebug() << "Connected";
    else qDebug() << "Not connected";

    while(true)
    {
        ;
    }
}

void TestUPower::updateProperties(QString s, QMap<QString, QVariant> dict, QStringList l)
{
    qDebug() << "update";
}

QTEST_MAIN (TestUPower);
