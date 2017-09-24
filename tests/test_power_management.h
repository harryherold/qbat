#ifndef TEST_POWERMANAGEMENT_H
#define TEST_POWERMANAGEMENT_H

#include <QtTest/QtTest>

class TestPowerManager : public QObject
{
    Q_OBJECT
    private slots:
    void query_device_paths ();
};

#endif // TEST_POWERMANAGEMENT_H