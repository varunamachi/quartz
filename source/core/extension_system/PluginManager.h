#pragma once

#include <memory>

#include <QString>
#include <QList>


#include "../utils/Macros.h"

namespace Quartz {

QZ_INTERFACE IPlugin;
QZ_INTERFACE IPluginAdapter;

class PluginManager
{
public:
    QZ_NO_COPY( PluginManager );

    PluginManager();

    ~PluginManager();


    bool loadFrom( const QString &location );

    bool destroy();

    IPlugin * plugin() const;

    IPluginAdapter * adapter() const;

    void registerPluginAdapter( IPluginAdapter *pluginHost );

private:
    class Data;
    std::unique_ptr< Data > m_data;

};

}
