#pragma once

#include <QtTest/QtTest>

class TestPowerManager : public QObject
{
    Q_OBJECT
private slots:
    void query_device_paths();

};