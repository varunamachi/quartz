#include <QMessageBox>

#include <core/logger/Logging.h>
#include <base/QzAppContext.h>
#include <base/content_manager/ContentManager.h>

#include "QzBinding.h"

namespace Quartz {

void QzBinding::info(const QString& module, const QString& msg) {
    QZ_INFO(module) << msg;
}

void QzBinding::error(const QString& module, const QString& msg) {
    QZ_ERROR(module) << msg;
}

void QzBinding::statusSuccess(const QString& operation, const QString& msg) {
    QMessageBox::information(appContext()->contentManager(),
                             "Quartz: " + operation,
                             msg,
                             QMessageBox::Ok);
}

void QzBinding::statusFailure(const QString& operation, const QString& msg) {
    QMessageBox::critical(appContext()->contentManager(),
                          "Quartz " + operation,
                          msg,
                          QMessageBox::Ok);
}

bool QzBinding::confirm(const QString& operation, const QString& msg) {
    auto result = QMessageBox::question(appContext()->contentManager(),
                                        "Quartz: " + operation,
                                        msg,
                                        QMessageBox::No | QMessageBox::Yes,
                                        QMessageBox::No);
    return result == QMessageBox::Yes;
}

} // namespace Quartz
