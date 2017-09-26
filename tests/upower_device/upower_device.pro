TEMPLATE = app

include(../../defaults.pri)

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

QT += testlib dbus

TARGET = test_upower_device
HEADERS += test_upower_device.h $$INCLUDEPATH/upower_device.h
SOURCES += test_upower_device.cpp $$SRC_DIR/upower_device.cpp
