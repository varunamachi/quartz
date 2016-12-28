
#include <QIcon>

#include "AbstractConfigPage.h"

namespace Quartz {

struct AbstractConfigPage::Data
{
    Data( const QStringList &parentPath ,
          const QString &name,
          const QString &id,
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

AbstractConfigPage::AbstractConfigPage( const QStringList &parentPath,
                                        const QString &name,
                                        const QString &id,
                                        const QIcon &icon,
                                        QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ parentPath, name, id, icon }}
{

}

AbstractConfigPage::~AbstractConfigPage()
{

}

const QString & AbstractConfigPage::configPageName() const
{
    return m_data->m_name;
}

const QStringList &AbstractConfigPage::parentPath() const
{
    return m_data->m_parentPath;
}

const QString & AbstractConfigPage::configPageId() const
{
    return m_data->m_id;
}

const QIcon &AbstractConfigPage::icon() const
{
    return m_data->m_icon;
}


}
