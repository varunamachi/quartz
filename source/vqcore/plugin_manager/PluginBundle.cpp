
#include <QList>
#include <std::string>
#include <std::stringList>

#include "AbstractPlugin.h"
#include "PluginBundle.h"

namespace Vam {


class PluginBundle::Impl
{
public:
    Impl( const std::string &bundleId,
          const std::string &bundleName )
        : m_bundleId( bundleId )
        , m_bundleName( bundleName )
    {

    }

    const std::string & bundleId() const
    {
        return m_bundleId;
    }

    const std::string & bundleName() const
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

    virtual void addDependency( const std::string &bundleId )
    {
        m_dependencies << bundleId;
    }

    const std::stringList & dependencies() const
    {
        return m_dependencies;
    }

    QList< std::shared_ptr< AbstractPlugin >> & mutablePluginList()
    {
        return  m_plugins;
    }

    std::stringList & mutalbleDependencyList()
    {
        return m_dependencies;
    }

private:
    std::string m_bundleId;

    std::string m_bundleName;

    std::stringList m_dependencies;

    QList< std::shared_ptr< AbstractPlugin >> m_plugins;
};


PluginBundle::PluginBundle( const std::string &bundleId,
                            const std::string &bundleName )
    : m_impl( std::make_unique< PluginBundle::Impl >( bundleId, bundleName ))
{

}


const std::string & PluginBundle::bundleId() const
{
    return m_impl->bundleId();
}


const std::string & PluginBundle::bundleName() const
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


void PluginBundle::addDependency( const std::string &bundleId )
{
    m_impl->addDependency( bundleId );
}


const std::stringList & PluginBundle::dependencies() const
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


std::stringList & PluginBundle::mutalbleDependencyList()
{
    return m_impl->mutalbleDependencyList();
}
