
#include <QIcon>

#include "AbstractConfigPage.h"

namespace Quartz {

struct AbstractConfigPage::Data
{
    Data( const QString &id,
          const QString &name,
          const QStringList &parentPath ,
          const QIcon &icon )
        : m_id( id )
        , m_name( name )
        , m_parentPath( parentPath )
        , m_icon( icon )
    {

    }

    const QString m_id;

    const QString m_name;

    const QStringList m_parentPath;

    const QIcon m_icon;

};

AbstractConfigPage::AbstractConfigPage( const QString &id,
                                        const QString &name,
                                        const QStringList &parentPath,
                                        const QIcon &icon,
                                        QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ id, name, parentPath, icon }}
{

}

AbstractConfigPage::~AbstractConfigPage()
{

}

const QString & AbstractConfigPage::configPageName() const
{
    return m_data->m_id;
}

const QStringList &AbstractConfigPage::parentPath() const
{
    return m_data->m_parentPath;
}

const QIcon &AbstractConfigPage::icon() const
{
    return m_data->m_icon;
}

const QString & AbstractConfigPage::configPageId() const
{
    return m_data->m_name;
}

}
