#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <cmath>
#include "battery_window.h"

#include <QDebug>
BatteryWindow::BatteryWindow()
{
    QDBusConnection system_bus = QDBusConnection::systemBus ();

    m_upower = new UPower("org.freedesktop.UPower",
                          "/org/freedesktop/UPower",
                          system_bus);

    bool ret = system_bus.connect("org.freedesktop.UPower",
                                  "/org/freedesktop/UPower",
                                  "org.freedesktop.DBus.Properties",
                                  "PropertiesChanged",
                                  this,
                                  SLOT(updateUPowerProperties(QString, QMap<QString, QVariant>,QStringList)));
    if(! ret)
    {
        qFatal("Cannot connect to upower dbus signal");
    }

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateIcon()));
    m_timer->start(5000);

    initializePowerDevices();

    createActions();
    createTrayIcon();

    updateIcon();
}

BatteryWindow::~BatteryWindow()
{
    for(UPowerDevice * dev : m_upower_devices)
    {
        delete dev;
    }
}

void BatteryWindow::initializePowerDevices()
{
    QDBusPendingReply<QList<PowerDevicePath>> reply = m_upower->EnumerateDevices ();
    reply.waitForFinished();

    if(! reply.isValid())
    {
        qFatal("Quering power devices failed");
    }

    for(const PowerDevicePath & dp: reply.value())
    {
        UPowerDevice * dev = new UPowerDevice("org.freedesktop.UPower",
                                              dp.path(),
                                              QDBusConnection::systemBus (),
                                              this);
        if(dev->type() == 2 && dev->nativePath().contains("BAT"))
        {
            qDebug() << "Add device " << dev->nativePath();
            m_upower_devices.append(dev);
        }
        else
        {
            delete dev;
        }
    }
}

void BatteryWindow::createTrayIcon()
{
    QIcon icon(*pix);

    m_trayIconMenu = new QMenu();
    m_trayIconMenu->addAction(m_quitAction);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(icon);
    m_trayIcon->setContextMenu(m_trayIconMenu);
    m_trayIcon->show();
}

void BatteryWindow::createActions()
{
    m_quitAction = new QAction(tr("quit"), this);
    connect(m_quitAction, SIGNAL(triggered()), this, SLOT(quit()));
}

void BatteryWindow::quit()
{
    exit(0);
}

void BatteryWindow::updateUPowerProperties(QString s, QMap<QString, QVariant> dict, QStringList sl)
{
    if(dict.contains(QString("OnBattery")))
    {
        updateIcon();
    }
}

uint BatteryWindow::getBatteryLevel()
{
    double total_percentage = 0;
    for(const UPowerDevice * dev: m_upower_devices)
    {
        total_percentage += dev->percentage();
    }

    total_percentage /= (m_upower_devices.count() * 100);
    total_percentage *= 100;
    qDebug() << "[getBatteryLevel] : current battery status " << total_percentage;
    return (uint) floor(total_percentage /(double) 20);
}

void BatteryWindow::updateIcon()
{
    qDebug() << "[updateIcon] : Update systray icon";
    QString image = "";
    uint level = getBatteryLevel();
    if(m_upower->onBattery())
    {
        image = QString(m_iconPathTemplate).arg("battery", QString::number(level));
    }
    else
    {
        image = QString(m_iconPathTemplate).arg("charging", QString::number(level));
    }
    m_trayIcon->setIcon(QIcon(image));
}