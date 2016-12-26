
#include "AbstractConfigPage.h"

namespace Quartz {

struct AbstractConfigPage::Data
{
    Data( const QString &id,
          const QString &name )
        : m_id( id )
        , m_name( name )
    {

    }

    const QString m_id;

    const QString m_name;

};

AbstractConfigPage::AbstractConfigPage( const QString &id,
                                        const QString &name,
                                        QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ id, name }}
{

}

AbstractConfigPage::~AbstractConfigPage()
{

}

const QString & AbstractConfigPage::configPageName() const
{
    return m_data->m_id;
}

const QString & AbstractConfigPage::configPageId() const
{
    return m_data->m_name;
}

}
