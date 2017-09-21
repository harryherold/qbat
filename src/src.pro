include(../defaults.pri)

CONFIG   += console

QT += dbus

TEMPLATE = lib

TARGET = powermanager
SOURCES += powermanager.cpp
HEADERS += ../include/powermanager.h