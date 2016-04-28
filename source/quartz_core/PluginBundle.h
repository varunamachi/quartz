#pragma once

#include <vector>

#include <QObject>
#include <QLibrary>

#include "IQuartzPlugin.h"
#include "QuartzCore.h"

namespace Vam { namespace Quartz {

class PluginBundle
{
public:
    PluginBundle( QString bundleId,
                  QString bundleName )
        : m_bundleId( bundleId )
        , m_bundleName( bundleName )
    {

    }

    const QString & bundleId() const
    {
        return m_bundleId;
    }

    const QString & bundleName() const
    {
        return m_bundleName;
    }

    virtual void addPlugin( IQuartzPlugin *plugin )
    {
        m_plugins.append( plugin );
    }

    int pluginCount() const
    {
        return m_plugins.size();
    }

    IQuartzPlugin * pluginAt( int index ) const
    {
        IQuartzPlugin *plugin = nullptr;
        if( index < m_plugins.size() ) {
            plugin = m_plugins.at( index );
        }
        return plugin;
    }

    virtual void addDependency( QString bundleId )
    {
        m_dependencies << bundleId;
    }

    const QStringList & dependencies() const
    {
        return m_dependencies;
    }

protected:
    QList< IQuartzPlugin > & mutablePluginList()
    {
        return m_plugins;
    }

    QStringList & mutalbleDependencyList()
    {
        return m_dependencies;
    }

private:


    QString m_bundleId;

    QString m_bundleName;

    QStringList m_dependencies;

    QList< IQuartzPlugin * > m_plugins;
};


} }


