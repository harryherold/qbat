#include "test_upower_device.h"

void TestUPowerDevice::get_device_types ()
{
    UPowerDevice dev ("org.freedesktop.UPower", "org.freedesktop.UPower/devices/battery_BAT0",
                      QDBusConnection::systemBus ());

    QVERIFY (QDBusConnection::systemBus ().isConnected ());

    QVERIFY (dev.type () == 2);
}

QTEST_MAIN (TestUPowerDevice);