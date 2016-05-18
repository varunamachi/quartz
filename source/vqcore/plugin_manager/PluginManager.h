#pragma once

#include <vector>
#include <string>
#include <memory>

#include "../common/Result.h"
#include "../common/Macros.h"
#include "../VQ.h"

namespace Vam {

class PluginBundle;
class AbstractPlugin;
class AbstractPluginSlot;

class VQ_CORE_EXPORT PluginManager
{
public:
    PluginManager( std::string location );

    Result< bool > loadAll();

    Result< bool > unloadAll();

    Result< bool > reloadAll();

    Result< bool > unload( const std::string &bundleId );

    Result< bool > load( const std::string &bundleId );

    Result< bool > reload( const std::string &bundleId );

    Result< PluginBundle * > pluginBundle( const std::string &bundleId ) const;

    Result< bool > allBundles(
            VQ_OUT std::vector< const PluginBundle * > &bundlesOut ) const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

}
