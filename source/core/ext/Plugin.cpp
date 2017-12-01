
#include <QString>
#include <QLibrary>

#include "Plugin.h"

namespace Quartz { namespace Ext {

struct Plugin::Data
{
    Data( const QString & pluginId,
          const QString & pluginName )
        : m_pluginId( pluginId )
        , m_pluginName( pluginName )
    {

    }

    QString m_pluginId;

    QString m_pluginName;

    QzCoreContext *m_context;
};

Plugin::Plugin(
        const QString &pluginId,
        const QString &pluginName )
    : m_data( new Plugin::Data{ pluginId, pluginName })
{

}

Plugin::~Plugin()
{

}

const QString & Plugin::pluginId() const
{
    return m_data->m_pluginId;
}

const QString &Plugin::pluginName() const
{
    return m_data->m_pluginName;
}

void Plugin::setContext( QzCoreContext *context )
{
    m_data->m_context = context;
}

QzCoreContext *Plugin::coreContext() const
{
    return m_data->m_context;
}

} }
