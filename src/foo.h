#ifndef FOO_H
#define FOO_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

class Foo: public QObject
{
    Q_OBJECT

    public:
    Foo (QObject * parent=NULL);
    public slots:
    void updateProperties (QString s, QMap<QString, QVariant> dict, QStringList l);
};

#endif //FOO_H