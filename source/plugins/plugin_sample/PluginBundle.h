#pragma once

#include <core/extension_system/AbstractPluginBundle.h>

namespace Quartz {

class QzAppContext;

namespace Plugin { namespace Sample {

class PluginBundle : public AbstractPluginBundle
{

public:
    PluginList plugins() const override;

    const QVector< QString > & dependencies( DependencyType depType ) const;

    PluginBundle();

    ~PluginBundle();

    static const QString BUNDLE_ID;

    static const QString BUNDLE_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
