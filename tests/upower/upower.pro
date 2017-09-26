TEMPLATE = app

include(../../defaults.pri)

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

QT += testlib dbus

TARGET = test_upower
HEADERS += test_upower.h $$INCLUDEPATH/upower.h
SOURCES += test_upower.cpp $$SRC_DIR/upower.cpp

# LIBS += -L../src -lpowermanager -Wl,-rpath=$$SRC_DIR