#include "battery_icon.h"
#include <QDebug>

BatteryIcon::BatteryIcon(UPowerDevice * dev, QObject* parent)
 :QObject(parent),
  m_upowerDevice(dev),
  m_trayIcon(nullptr),
  m_trayIconMenu(nullptr),
  m_quitAction(nullptr),
  m_batteryPic(nullptr),
  m_boltPic(nullptr),
  m_progressRect(12, 80, 210, 98),
  m_boltSourceRect(0, 0, 128, 128),
  m_boltTargetRect(m_progressRect.center().rx() - (m_boltSourceRect.width() / 2.),
                  m_progressRect.center().ry() - (m_boltSourceRect.height() / 2.) + 15.,
                  m_progressRect.height(),
                  m_progressRect.height())
{
    m_batteryPic = new QPixmap("/home/cherold/cpp-workspace/qbat/images/battery.png");
    m_boltPic = new QPixmap("/home/cherold/cpp-workspace/qbat/images/bolt.png");

    m_quitAction = new QAction(tr("quit"), this);
    connect(m_quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    m_trayIconMenu = new QMenu();
    m_trayIconMenu->addAction(m_quitAction);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(*m_batteryPic));
    m_trayIcon->setContextMenu(m_trayIconMenu);
    m_trayIcon->show();
}

BatteryIcon::~BatteryIcon()
{
    delete m_upowerDevice;
    delete m_batteryPic;
    delete m_boltPic;
    delete m_trayIconMenu;
    delete m_trayIcon;
    delete m_quitAction;
}

QColor BatteryIcon::getColor(double percentage)
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

void BatteryIcon::quit(void)
{
    // TODO Is there a better way?
    exit(0);
}

void BatteryIcon::update(void)
{
    BatteryState state = static_cast<BatteryState>(m_upowerDevice->state());
    double percentage = m_upowerDevice->percentage();
    qDebug() << "[BatteryIcon] : " << "draw icon with " << percentage << "percentage";
    qDebug() << "[BatteryIcon] : " << "state " << static_cast<int>(state);
    QPixmap pix(*m_batteryPic);
    QPainter painter(&pix);

    m_progressRect.setSize(QSize((percentage * 210) /100, 98));

    QColor progress_color(getColor(percentage));
    QPen pen(progress_color);
    QPainterPath path;

    painter.setRenderHint(QPainter::Antialiasing);
    path.addRoundedRect(m_progressRect, 10, 10);
    painter.setPen(pen);
    painter.fillPath(path, progress_color);
    painter.drawPath(path);

    if(state == BatteryState::CHARGING)
    {
        qDebug() << "[BatteryIcon] : " << "draw bolt";
        painter.drawPixmap(m_boltTargetRect, *m_boltPic, m_boltSourceRect);
    }
    m_trayIcon->setIcon(QIcon(pix));
}