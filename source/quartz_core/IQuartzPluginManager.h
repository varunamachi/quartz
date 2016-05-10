#pragma once

#include <vqcore/VQCommon.h>
#include <vqcore/common/Result.h>

#include "PluginBundle.h"

namespace Vam { namespace Quartz {

VQ_INTERFACE IQuartzPluginManager
{
    virtual Result< PluginBundle * > pluginBundle(
                const QString &bundleId ) const = 0;

    virtual Result< QList< const PluginBundle * >> allBundles() const = 0;

    virtual Result< bool > loadAll() = 0;

    virtual Result< bool > unloadAll() = 0;

    virtual Result< bool > reloadAll() = 0;

    virtual Result< bool > unload( QString bundleId ) = 0;

    virtual Result< bool > load( QString bundleId ) = 0;

    virtual Result< bool > reload( QString bundleId ) = 0;

    virtual ~IQuartzPluginManager() { }
};


} }
