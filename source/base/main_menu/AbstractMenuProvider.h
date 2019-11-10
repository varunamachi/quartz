#pragma once

#include <core/ext/Extension.h>

class QAction;
class QMenu;

namespace Quartz {

class AbstractMenuProvider : public Ext::Extension {
public:
    AbstractMenuProvider(const QString& pluginId, const QString& pluginName);

    virtual QVector<QAction*> actions() const = 0;

    virtual QVector<QMenu*> menus() const = 0;

    const static QString EXTENSION_TYPE;
};

} // namespace Quartz
