#ifndef TEST_UPOWER_H
#define TEST_UPOWER_H

#include <QtTest/QtTest>
#include <upower.h>

class TestUPower : public QObject
{
    Q_OBJECT

    using PowerDevicePath = QDBusObjectPath;
    using UPower = OrgFreedesktopUPowerInterface;
public slots:
    void updateProperties(QString s, QMap<QString, QVariant> dict, QStringList l);
private slots:
    void query_device_paths ();
};

#endif // TEST_UPOWER_H