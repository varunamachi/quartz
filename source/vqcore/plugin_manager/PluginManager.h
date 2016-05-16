#pragma once

#include <QSet>
#include <QHash>
#include <QMultiHash>

#include "BundleLoader.h"

namespace Vam {

class PluginBundle;
class AbstractPlugin;
class AbstractPluginSlot;

class PluginManager
{
public:
    PluginManager( std::string location )
        : m_location( location )
    {

    }

    Result< bool > loadAll();

    Result< bool > unloadAll();

    Result< bool > reloadAll();

    Result< bool > unload( std::string bundleId );

    Result< bool > load( std::string bundleId );

    Result< bool > reload( std::string bundleId );

    Result< PluginBundle * > pluginBundle( const std::string &bundleId ) const;

    Result< QList< const PluginBundle * >> allBundles() const;

private:
    Result< bool > loadBundle( const PluginBundle &bundle,
                               VQ_IN_OUT QSet< std::string > &loadedBundles );

    Result< bool > unloadBundle( const PluginBundle &bundle,
                                 VQ_IN_OUT QSet< std::string > &unloadedBundles );

    QHash< std::string, std::shared_ptr< BundleLibrary >> m_libraries;

    QMultiHash< std::string, std::string > m_dependents;

    std::string m_location;

    BundleLoader m_loader;

};

}
