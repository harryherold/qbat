TEMPLATE = app

include(../defaults.pri)

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

QT += testlib dbus
TARGET = test_power_management
HEADERS += test_power_management.h
SOURCES += test_power_management.cpp

LIBS += -L../src -lpowermanager -Wl,-rpath=$$SRC_DIR