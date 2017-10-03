#include <QApplication>
#include "battery_window.h"

int main (int argc, char **argv)
{
    QApplication app (argc, argv);

    BatteryWindow bat;

    return app.exec ();
}
