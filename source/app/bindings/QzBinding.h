#pragma once

#include <QObject>

class QQmlEngine;
class QJSEngine;

class Qz : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void info( QString module, QString msg );

    Q_INVOKABLE void error( QString module, QString msg );

    Q_INVOKABLE void statusSuccess( QString msg );

    Q_INVOKABLE void statusFailure( QString msg );

    static QObject *qmlInstance( QQmlEngine */*engine*/,
                                 QJSEngine */*scriptEngine*/ )
    {
        return new Qz{};
    }

private:

};
