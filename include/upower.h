/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was:
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef UPOWER_H
#define UPOWER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.freedesktop.UPower
 */
class OrgFreedesktopUPowerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.UPower"; }

public:
    OrgFreedesktopUPowerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~OrgFreedesktopUPowerInterface();

    Q_PROPERTY(QString DaemonVersion READ daemonVersion)
    inline QString daemonVersion() const
    { return qvariant_cast< QString >(property("DaemonVersion")); }

    Q_PROPERTY(bool LidIsClosed READ lidIsClosed)
    inline bool lidIsClosed() const
    { return qvariant_cast< bool >(property("LidIsClosed")); }

    Q_PROPERTY(bool LidIsPresent READ lidIsPresent)
    inline bool lidIsPresent() const
    { return qvariant_cast< bool >(property("LidIsPresent")); }

    Q_PROPERTY(bool OnBattery READ onBattery)
    inline bool onBattery() const
    { return qvariant_cast< bool >(property("OnBattery")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QList<QDBusObjectPath> > EnumerateDevices()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("EnumerateDevices"), argumentList);
    }

    inline QDBusPendingReply<QString> GetCriticalAction()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetCriticalAction"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> GetDisplayDevice()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetDisplayDevice"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void DeviceAdded(const QDBusObjectPath &device);
    void DeviceRemoved(const QDBusObjectPath &device);
};

#endif
