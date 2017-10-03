include(../defaults.pri)

#CONFIG   += console

QT += dbus core gui widgets

TEMPLATE = app

TARGET = qbat
SOURCES += qbat.cpp upower.cpp upower_device.cpp battery_window.cpp
HEADERS += ../include/upower_device.h ../include/upower.h battery_window.h
