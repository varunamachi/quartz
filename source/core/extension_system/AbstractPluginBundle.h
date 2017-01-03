#pragma once

#include <memory>

#include <QPair>

#include "../QuartzCore.h"


class QString;

namespace Quartz {

class QzCoreContext;
class AbstractPlugin;
class BundleEnv;


enum class DependencyType
{
    Required,
    Optional
};

using PluginList = QVector< std::shared_ptr< AbstractPlugin >>;
using DependencyList = QVector< QPair< QString, DependencyType >>;

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

    virtual const PluginList & plugins() const = 0;

    virtual const DependencyList & dependencies() const = 0;

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

struct BundleInputWrapper {
    std::unique_ptr< Quartz::BundleEnv > env;
    Quartz::QzCoreContext *appContext;

};

}

