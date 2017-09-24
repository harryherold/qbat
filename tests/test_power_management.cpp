#include "test_power_management.h"
#include <powermanager.h>

void TestPowerManager::query_device_paths ()
{
    PowerManagement pm;
    qDebug () << pm.getPowerDeviceCount ();
    // QList<QString> expected_paths = {
    //     "/org/freedesktop/UPower/devices/battery_BAT0",
    //     "/org/freedesktop/UPower/devices/battery_BAT1",
    //     "/org/freedesktop/UPower/devices/line_power_AC"};

    // QVERIFY(devices.count() == expected_paths.count());

    // for(int i = 0; i < devices.count(); i++)
    // {
    //   QCOMPARE(devices.at(i).path(), expected_paths.at(i));
    // }
}

QTEST_MAIN (TestPowerManager);
