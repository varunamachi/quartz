#pragma once

#include <core/extension_system/AbstractPluginBundle.h>

namespace Quartz {

class QzAppContext;

namespace Plugin { namespace Sample {

class PluginBundle : public AbstractPluginBundle
{

public:
    const PluginList & plugins() const override;

    const DependencyList & dependencies() const override;

    PluginBundle();

    ~PluginBundle();

    static const QString BUNDLE_ID;

    static const QString BUNDLE_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
