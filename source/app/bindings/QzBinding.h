#pragma once

#include <QObject>

class Qz : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void info( QString msg );

    Q_INVOKABLE void statusSuccess( QString msg );

    Q_INVOKABLE void statusFailure( QString msg );

private:

};
