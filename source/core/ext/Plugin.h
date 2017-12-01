#pragma once

#include <memory>

#include <QPair>

#include "../QuartzCore.h"
#include "../utils/Macros.h"


class QString;

namespace Quartz {

class QzCoreContext;

namespace Ext {

class Extension;
class PluginEnv;
QZ_INTERFACE IExtensionAdapter;


enum class DependencyType
{
    Required,
    Optional
};

using PluginList = QVector< std::shared_ptr< Extension >>;
using DependencyList = QVector< QPair< QString, DependencyType >>;
using AdapterList = QVector< std::shared_ptr< IExtensionAdapter >>;

class QUARTZ_CORE_API Plugin
{
public:

    Plugin( const QString &pluginId,
            const QString &pluginName );

    virtual ~Plugin();

    const QString & pluginId() const;

    const QString & pluginName() const;

    void setContext( QzCoreContext *context );

    QzCoreContext * coreContext() const;

    virtual const PluginList & extensions() const = 0;

    virtual const AdapterList & adapters() const = 0;

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

struct PluginWrapper {
    Quartz::Ext::Plugin *plugin;
};

struct PluginInputWrapper {
    std::unique_ptr< Quartz::Ext::PluginEnv > env;
    Quartz::QzCoreContext *appContext;

};

} }

