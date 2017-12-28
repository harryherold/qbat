#include "battery_window.h"
#include <utils.h>

#include <QDebug>

BatteryWindow::BatteryWindow()
: m_timer(nullptr),
  m_upower(nullptr),
  m_trayIcon(nullptr),
  m_progressRect(0, 0, 0, 0),
  m_batteryRect(0, 0, width, height)
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
    m_trayIcon = new QSystemTrayIcon(this);
    initializePowerDevices();
    update();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(5000);
}

BatteryWindow::~BatteryWindow()
{
    for(UPowerDevice * dev: m_devices)
    {
        delete dev;
    }
    delete m_upower;
    delete m_trayIcon;
    delete m_timer;
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
            m_devices.append(dev);
        }
        else
        {
            delete dev;
        }
    }
}

void BatteryWindow::updateUPowerProperties(QString, QMap<QString, QVariant> dict, QStringList)
{
    if(dict.contains(QString("OnBattery")))
    {
        qDebug() << "[BatteryWindow] : Updated upower properties";
        emit powerStateChanged();
    }
}

QColor BatteryWindow::getColor(double percentage)
{
    if(percentage < 20.0)
        return Qt::red;
    else if(percentage <= 50.0)
        return Qt::yellow;
    else if(percentage <= 80.0)
        return Qt::blue;
    else
        return Qt::green;
}

double
BatteryWindow::getAccumulatedPercentage()
{
    double sum = 0.0;
    for(UPowerDevice * dev: m_devices)
    {
        sum += dev->percentage();
    }
    return sum / m_devices.count();
}

double
BatteryWindow::getAccumulatedTime()
{
    double time = 0.0;
    for(UPowerDevice * dev: m_devices)
    {
        time += dev->timeToEmpty();
    }
    return time;
}

void BatteryWindow::update(void)
{
    auto state = m_upower->onBattery() ? BatteryState::DISCHARGING : BatteryState::CHARGING;
    auto percentage = getAccumulatedPercentage();
    qDebug() << "Update icon " << percentage << "\%";
    drawIcon(percentage, state);
    double secs = getAccumulatedTime();
    int hours = secs / 3600;
    int mins = (secs / 60) - (hours * 60);
    m_trayIcon->setToolTip(QString("Time: %1 hours, %2 mins").arg(hours).arg(mins));
}

void BatteryWindow::drawIcon(double percentage, BatteryState state)
{
    QPixmap pix(width, height);
    QPainter painter(&pix);

    QPainterPath battery_path;
    battery_path.addRoundedRect(m_batteryRect, 10, 10);
    painter.fillPath(battery_path, Qt::white);
    painter.drawPath(battery_path);

    const int h = (percentage * height) / 100;
    m_progressRect.setSize(QSize(width, h));
    m_progressRect.moveTo(0, height - h);

    QColor progress_color(getColor(percentage));
    QPen pen(progress_color);

    QPainterPath path;
    painter.setRenderHint(QPainter::Antialiasing);
    path.addRoundedRect(m_progressRect, 10, 10);

    painter.fillPath(path, progress_color);
    painter.drawPath(path);

    if(state == BatteryState::CHARGING)
    {
        qDebug() << "[BatteryIcon] : " << "draw bolt";
    }

    m_trayIcon->setIcon(QIcon(pix));
    m_trayIcon->show();
}