
#include "AbstractPlugin.h"
#include "PluginBundle.h"

namespace Vq {


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

    virtual void addPlugin( std::unique_ptr< AbstractPlugin > plugin )
    {
        m_plugins.emplace_back( std::move( plugin ));
    }

    std::size_t pluginCount() const
    {
        return m_plugins.size();
    }

    AbstractPlugin * pluginAt( const std::size_t index ) const
    {
        AbstractPlugin *plugin = nullptr;
        if( index < m_plugins.size() ) {
            plugin = m_plugins.at( index ).get();
        }
        return plugin;
    }

    virtual void addDependency( const std::string &bundleId )
    {
        m_dependencies.emplace_back( bundleId );
    }

    const std::vector< std::string > & dependencies() const
    {
        return m_dependencies;
    }

    std::vector< std::unique_ptr< AbstractPlugin >> & mutablePluginList()
    {
        return  m_plugins;
    }

    std::vector< std::string > & mutalbleDependencyList()
    {
        return m_dependencies;
    }

private:
    std::string m_bundleId;

    std::string m_bundleName;

    std::vector< std::string > m_dependencies;

    std::vector< std::unique_ptr< AbstractPlugin >> m_plugins;
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


void PluginBundle::addPlugin( std::unique_ptr< AbstractPlugin > plugin )
{
    m_impl->addPlugin( std::move( plugin ));
}


std::size_t PluginBundle::pluginCount() const
{
    return m_impl->pluginCount();
}


AbstractPlugin * PluginBundle::pluginAt( const std::size_t index ) const
{
    return m_impl->pluginAt( index );
}


void PluginBundle::addDependency( const std::string &bundleId )
{
    m_impl->addDependency( bundleId );
}


const std::vector< std::string > & PluginBundle::dependencies() const
{
    return m_impl->dependencies();
}


PluginBundle::~PluginBundle()
{
    //
}


std::vector< std::unique_ptr< AbstractPlugin >> &
PluginBundle::mutablePluginList()
{
    return m_impl->mutablePluginList();
}


std::vector< std::string > & PluginBundle::mutalbleDependencyList()
{
    return m_impl->mutalbleDependencyList();
}
