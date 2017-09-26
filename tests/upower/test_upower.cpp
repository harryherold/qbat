#include "test_upower.h"
#include <unistd.h>

void TestUPower::query_device_paths ()
{
    UPower upower("org.freedesktop.UPower",
                  "/org/freedesktop/UPower",
                  QDBusConnection::systemBus ());

    QVERIFY( QDBusConnection::systemBus().isConnected() );

    QDBusPendingReply<QList<PowerDevicePath>> reply = upower.EnumerateDevices ();

    reply.waitForFinished();

    QVERIFY(reply.isValid ());

    QVERIFY(upower.onBattery() == false);
}

QTEST_MAIN (TestUPower);
