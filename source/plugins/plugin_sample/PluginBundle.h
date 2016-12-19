#pragma once

#include <core/extension_system/AbstractPluginBundle.h>

namespace Quartz {

class QzAppContext;

namespace Plugin { namespace Sample {

class PluginBundle : public AbstractPluginBundle
{

public:
    PluginList plugins() const override;

    static PluginBundle * get();

    static QzAppContext * appContext();

    static void destroy();

    ~PluginBundle();

    static const QString BUNDLE_ID;

    static const QString BUNDLE_NAME;

private:
    PluginBundle();

    static std::unique_ptr< PluginBundle > s_instance;
};

} } }
