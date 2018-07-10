#include <QIcon>

#include "AbstractSelector.h"

namespace Quartz {

struct AbstractSelector::Data
{
    Data( const QString &id,
          const QString &name,
          const QIcon &icon)
        : m_id(id)
        , m_name(name)
        , m_icon(icon)
    {

    }

    QString m_id;

    QString m_name;

    QIcon m_icon;

};


AbstractSelector::AbstractSelector( const QString &id,
                                    const QString &name,
                                    const QIcon &icon,
                                    QWidget *parent )
    : QWidget( parent )
    , m_data(std::make_unique< AbstractSelector::Data >( id, name, icon))
{

}

AbstractSelector::~AbstractSelector()
{

}

const QString & AbstractSelector::selectorId() const
{
    return m_data->m_id;
}

const QString & AbstractSelector::selectorName() const
{
    return m_data->m_name;
}

const QIcon &AbstractSelector::icon() const
{
    return m_data->m_icon;
}

}
