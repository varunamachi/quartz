#pragma once

#include <memory>


#include "../QuartzCore.h"


class QString;
class QLibrary;

namespace Quartz {

class QzCoreContext;
class AbstractPlugin;

using PluginList = QVector< std::shared_ptr< AbstractPlugin >>;


class QUARTZ_CORE_API AbstractPluginBundle
{
public:
    AbstractPluginBundle( const QString &bundleId,
                          const QString &bundleName );

    virtual ~AbstractPluginBundle();

    const QString & bundleId() const;

    const QString & bundleName() const;


    void setContext( QzCoreContext *context );

    QzCoreContext * coreContext() const;

    virtual PluginList plugins() const = 0;

    template< typename Context >
    Context * context() const
    {
        return static_cast< Context *>( coreContext() );
    }

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};


}

extern "C" {

struct PluginBundleWrapper {
    Quartz::AbstractPluginBundle *bundle;
};

}

