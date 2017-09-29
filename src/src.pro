include(../defaults.pri)

#CONFIG   += console

QT += dbus core gui widgets

TEMPLATE = app

TARGET = qbat
SOURCES += qbat.cpp upower.cpp upower_device.cpp foo.cpp
HEADERS += ../include/upower_device.h ../include/upower.h foo.h
