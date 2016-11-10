#include "AbstractSelector.h"

namespace Quartz {

struct AbstractSelector::Data
{
    Data( const Context *context,
          const QString &id,
          const QString &name )
        : m_context( context )
        , m_id( id )
        , m_name( name )
    {

    }

    const Context *m_context;

    QString m_id;

    QString m_name;

};


AbstractSelector::AbstractSelector( const Context *context,
                                    const QString &id,
                                    const QString &name,
                                    QWidget *parent )
    : QWidget( parent )
//    , m_data( std::make_unique< AbstractSelector::Data >( context, id, name ))
    , m_data( new AbstractSelector::Data( context, id, name ))
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

const Context *AbstractSelector::context() const
{
    return m_data->m_context;
}


}
