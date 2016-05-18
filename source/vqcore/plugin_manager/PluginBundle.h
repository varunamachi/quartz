#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../VQ.h"
#include "../common/Macros.h"


namespace Vam {

class AbstractPlugin;

class VQ_CORE_EXPORT PluginBundle
{
public:
    PluginBundle( const std::string &bundleId,
                  const std::string &bundleName );

    PluginBundle( PluginBundle &other ) = delete;

    PluginBundle & operator=( PluginBundle &other ) = delete;

    const std::string & bundleId() const;

    const std::string & bundleName() const;

    virtual void addPlugin( std::unique_ptr< AbstractPlugin > plugin );

    std::size_t pluginCount() const;

    AbstractPlugin * pluginAt( const std::size_t index ) const;

    virtual void addDependency( const std::string &bundleId );

    const std::vector< std::string > & dependencies() const;

    virtual ~PluginBundle();

protected:
    std::vector< std::unique_ptr< AbstractPlugin >> & mutablePluginList();

    std::vector< std::string > & mutalbleDependencyList();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};


}


struct VQ_CORE_EXPORT BundleWrapper {
    Vam::PluginBundle *theBundle;

};
