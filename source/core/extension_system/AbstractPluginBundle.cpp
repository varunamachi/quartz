
#include <QString>
#include <QLibrary>

#include "AbstractPluginBundle.h"

namespace Quartz {

struct AbstractPluginBundle::Data
{
    Data( const QString & bundleId,
          const QString & bundleName )
        : m_bundleId( bundleId )
        , m_bundleName( bundleName )
    {

    }

    QString m_bundleId;

    QString m_bundleName;

    QzCoreContext *m_context;
};

AbstractPluginBundle::AbstractPluginBundle(
        const QString &bundleId,
        const QString &bundleName )
    : m_data( new AbstractPluginBundle::Data{ bundleId, bundleName })
{

}

AbstractPluginBundle::~AbstractPluginBundle()
{

}

const QString &AbstractPluginBundle::bundleId() const
{
    return m_data->m_bundleId;
}

const QString &AbstractPluginBundle::bundleName() const
{
    return m_data->m_bundleName;
}

void AbstractPluginBundle::setContext( QzCoreContext *context )
{
    m_data->m_context = context;
}

QzCoreContext *AbstractPluginBundle::coreContext() const
{
    return m_data->m_context;
}

}
