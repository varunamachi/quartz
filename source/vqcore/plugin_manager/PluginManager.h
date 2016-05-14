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
    PluginManager( QString location )
        : m_location( location )
    {

    }

    Result< bool > loadAll();

    Result< bool > unloadAll();

    Result< bool > reloadAll();

    Result< bool > unload( QString bundleId );

    Result< bool > load( QString bundleId );

    Result< bool > reload( QString bundleId );

    Result< PluginBundle * > pluginBundle( const QString &bundleId ) const;

    Result< QList< const PluginBundle * >> allBundles() const;

private:
    Result< bool > loadBundle( const PluginBundle &bundle,
                               VQ_IN_OUT QSet< QString > &loadedBundles );

    Result< bool > unloadBundle( const PluginBundle &bundle,
                                 VQ_IN_OUT QSet< QString > &unloadedBundles );

    QHash< QString, std::shared_ptr< BundleLibrary >> m_libraries;

    QMultiHash< QString, QString > m_dependents;

    QString m_location;

    BundleLoader m_loader;

};

}
