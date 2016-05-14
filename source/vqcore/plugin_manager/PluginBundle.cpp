
#include <QList>
#include <QString>
#include <QStringList>

#include "AbstractPlugin.h"
#include "PluginBundle.h"

namespace Vam {


class PluginBundle::Impl
{
public:
    Impl( const QString &bundleId,
          const QString &bundleName )
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

    virtual void addPlugin( std::shared_ptr< AbstractPlugin > plugin )
    {
        m_plugins.append( plugin );
    }

    int pluginCount() const
    {
        return m_plugins.size();
    }

    AbstractPlugin * pluginAt( const int index ) const
    {
        AbstractPlugin *plugin = nullptr;
        if( index < m_plugins.size() ) {
            plugin = m_plugins.at( index ).get();
        }
        return plugin;
    }

    virtual void addDependency( const QString &bundleId )
    {
        m_dependencies << bundleId;
    }

    const QStringList & dependencies() const
    {
        return m_dependencies;
    }

    QList< std::shared_ptr< AbstractPlugin >> & mutablePluginList()
    {
        return  m_plugins;
    }

    QStringList & mutalbleDependencyList()
    {
        return m_dependencies;
    }

private:
    QString m_bundleId;

    QString m_bundleName;

    QStringList m_dependencies;

    QList< std::shared_ptr< AbstractPlugin >> m_plugins;
};


PluginBundle::PluginBundle( const QString &bundleId,
                            const QString &bundleName )
    : m_impl( std::make_unique< PluginBundle::Impl >( bundleId, bundleName ))
{

}


const QString & PluginBundle::bundleId() const
{
    return m_impl->bundleId();
}


const QString & PluginBundle::bundleName() const
{
    return m_impl->bundleName();
}


void PluginBundle::addPlugin( std::shared_ptr< AbstractPlugin > plugin )
{
    m_impl->addPlugin( plugin );
}


int PluginBundle::pluginCount() const
{
    return m_impl->pluginCount();
}


AbstractPlugin * PluginBundle::pluginAt( const int index ) const
{
    return m_impl->pluginAt( index );
}


void PluginBundle::addDependency( const QString &bundleId )
{
    m_impl->addDependency( bundleId );
}


const QStringList & PluginBundle::dependencies() const
{
    return m_impl->dependencies();
}


~PluginBundle::PluginBundle()
{
    //
}


QList< std::shared_ptr< AbstractPlugin >> & PluginBundle::mutablePluginList()
{
    return m_impl->mutablePluginList();
}


QStringList & PluginBundle::mutalbleDependencyList()
{
    return m_impl->mutalbleDependencyList();
}
