TEMPLATE = app

include(../defaults.pri)

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

QT += testlib dbus

TARGET = test_upower
HEADERS += test_upower.h
SOURCES += test_upower.cpp

TARGET += test_upower_device
HEADERS += test_upower_device.h
SOURCES += test_upower_device.cpp

LIBS += -L../src -lpowermanager -Wl,-rpath=$$SRC_DIR