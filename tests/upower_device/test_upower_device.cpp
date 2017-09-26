#include "test_upower_device.h"

void TestUPowerDevice::get_device_types ()
{
    UPowerDevice dev ("org.freedesktop.UPower",
                      "/org/freedesktop/UPower/devices/battery_BAT0",
                      QDBusConnection::systemBus ());

    QVERIFY (QDBusConnection::systemBus ().isConnected ());

    QVERIFY (dev.type () == 2);

    QCOMPARE(dev.nativePath(), QString("BAT0"));

    double accu_percentage = dev.percentage();

    QVERIFY(accu_percentage <= 100.0);

    qDebug() << accu_percentage;

    QVERIFY(accu_percentage >= 0.0);

    UPowerDevice dev2 ("org.freedesktop.UPower",
                       "/org/freedesktop/UPower/devices/line_power_AC",
                       QDBusConnection::systemBus ());

    QVERIFY (dev2.type () == 1);

    QCOMPARE(dev2.nativePath(), QString("AC"));
}

QTEST_MAIN (TestUPowerDevice);