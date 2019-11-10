#pragma once

#include <QObject>

class QQmlEngine;
class QJSEngine;

namespace Quartz {

class QzBinding : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void info(const QString& module, const QString& msg);

    Q_INVOKABLE void error(const QString& module, const QString& msg);

    Q_INVOKABLE void statusSuccess(const QString& operation,
                                   const QString& msg);

    Q_INVOKABLE void statusFailure(const QString& operation,
                                   const QString& msg);

    Q_INVOKABLE bool confirm(const QString& operation, const QString& msg);

    static QObject* qmlInstance(QQmlEngine* /*engine*/,
                                QJSEngine* /*scriptEngine*/) {
        return new QzBinding{};
    }

private:
};

} // namespace Quartz
