include(../defaults.pri)

QT += dbus core gui widgets

TEMPLATE = app

TARGET = qbat

SOURCES += qbat.cpp \
           upower.cpp \
           upower_device.cpp \
           battery_icon.cpp \
           battery_window.cpp

HEADERS += ../include/upower_device.h \
           ../include/upower.h \
           ../include/battery_icon.h \
           ../include/battery_window.h
