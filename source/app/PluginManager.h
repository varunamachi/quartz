#pragma once

#include <QSet>
#include <QHash>
#include <QMultiHash>

#include <quartz_core/IQuartzPlugin.h>

#include "BundleLoader.h"

namespace Vam { namespace Quartz {

class PluginManager
{
public:
    PluginManager( QuartzContext *context,
                   QString location )
        : m_location( location )
    {

    }

    bool loadAll();

    bool unloadAll();

    bool reloadAll();

    bool unload( QString bundleId );

    bool load( QString bundleId );

    bool reload( QString bundleId );

private:
    bool loadBundle( const PluginBundle &bundle,
                     VQ_IN_OUT QSet< QString > &loadedBundles );

    bool unloadBundle( const PluginBundle &bundle,
                       VQ_IN_OUT QSet< QString > &unloadedBundles );

    QHash< QString, BundleLibrary::Ptr > m_libraries;

    QMultiHash< QString, QString > m_dependents;

    QuartzContext *m_context;

    QString m_location;

    BundleLoader m_loader;

};


} }
