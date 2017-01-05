#pragma once

#include <memory>

#include <QVector>

#include "../QuartzCore.h"
#include "../utils/Macros.h"

class QDir;
class QString;
class QFileInfo;

namespace Quartz {

class AbstractPlugin;
class AbstractPluginBundle;
QZ_INTERFACE IPluginAdapter;

class QUARTZ_CORE_API PluginManager
{
public:
    QZ_NO_COPY( PluginManager );

    PluginManager();

    ~PluginManager();

    bool loadFrom( const QString &location );

    bool destroy();

    void registerPluginAdapter( std::shared_ptr< IPluginAdapter > adapter );

    void registerPluginAdapter( IPluginAdapter *adapter );

    const QVector< AbstractPluginBundle *> bundles() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

}
