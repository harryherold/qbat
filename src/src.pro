include(../defaults.pri)

CONFIG   += console

QT += dbus

TEMPLATE = lib

TARGET = powermanager
SOURCES += powermanager.cpp upower.cpp upower_device.cpp
HEADERS += ../include/powermanager.h ../include/upower_device.h ../include/upower.h