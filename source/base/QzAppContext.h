#pragma once

#include <memory>

#include <core/QzCoreContext.h>

#include "QuartzBase.h"

namespace Quartz {

class ContentManager;
class SelectorManager;
class GeneralSelector;
class ConfigPageManager;
class ThemeManager;
class NotificationService;
class ViewManager;

namespace Ext {
class PlugginManager;
}

enum class StdPath { DataDirectory, LogDirectory };

class QUARTZ_BASE_API QzAppContext : public QzCoreContext {
public:
    explicit QzAppContext();

    ~QzAppContext();

    QZCONTEXT_FUNC_DECL(ContentManager, contentManager);
    QZCONTEXT_FUNC_DECL(SelectorManager, selectorManager);
    QZCONTEXT_FUNC_DECL(GeneralSelector, nodeSelector);
    QZCONTEXT_FUNC_DECL(ConfigPageManager, configPageManager);
    QZCONTEXT_FUNC_DECL(ThemeManager, themeManager);
    QZCONTEXT_FUNC_DECL(NotificationService, notificationService);
    QZCONTEXT_FUNC_DECL(ViewManager, viewManager);

    static QString expand(StdPath pathID);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

inline QzAppContext* appContext() {
    return context<QzAppContext>();
}

} // namespace Quartz
