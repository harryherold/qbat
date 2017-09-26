#ifndef TEST_UPOWER_DEVICE_H
#define TEST_UPOWER_DEVICE_H

#include <QtTest/QtTest>
#include <upower_device.h>

class TestUPowerDevice : public QObject
{
    Q_OBJECT

    using UPowerDevice = OrgFreedesktopUPowerDeviceInterface;

    private slots:
    void get_device_types ();
};

#endif // TEST_UPOWER_DEVICE_H