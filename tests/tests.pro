TEMPLATE = app

include(../defaults.pri)

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

QT += testlib
TARGET = test_power_management
HEADERS += test_power_management.h
SOURCES += test_power_management.cpp

LIBS += -L../src -lpowermanager