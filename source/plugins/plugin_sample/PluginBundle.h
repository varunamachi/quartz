#pragma once

#include <core/extension_system/AbstractPluginBundle.h>

namespace Quartz {

class QzAppContext;

namespace Plugin { namespace Sample {

class PluginBundle : public AbstractPluginBundle
{

public:
    PluginList plugins() const override;

    PluginBundle();

    ~PluginBundle();

    static const QString BUNDLE_ID;

    static const QString BUNDLE_NAME;

};

} } }
