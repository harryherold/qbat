#include <QApplication>
#include "foo.h"

int main (int argc, char **argv)
{
    QApplication app (argc, argv);
    Foo *f = new Foo ();
    return app.exec ();
}
