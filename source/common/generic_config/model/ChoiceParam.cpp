#include <QVariant>
#include <QString>
#include <QHash>

#include "ChoiceParam.h"

namespace Quartz {

struct ChoiceParam::Data {

    Data()
        : m_defaultIndex{ -1 }
        , m_index{ m_defaultIndex }
    {

    }

    QList< QString > m_names;

    QHash< QString, QString > m_choices;

    int m_defaultIndex;

    int m_index;
};

ChoiceParam::ChoiceParam( const QString &id,
                          const QString &name,
                          const QString &description )
    : Param{ id, name, description }
    , m_data{ new Data{} }

{
}

ChoiceParam::~ChoiceParam()
{

}

void ChoiceParam::addOption( const QString &name, const QString &value )
{

    if( ! m_data->m_choices.contains( name )) {
        m_data->m_names.append( name );
        m_data->m_choices.insert( name, value );
    }
    if( m_data->m_defaultIndex == -1 ) {
        m_data->m_defaultIndex = 0;
    }
}

QString ChoiceParam::optionValue( const QString &name ) const
{
    QString value = m_data->m_choices.value( name, "" );
    return value;
}

QPair< QString, QString > ChoiceParam::option( int index ) const
{
    QPair< QString, QString > result;
    if( m_data->m_names.size() > index ) {
        auto name = m_data->m_names.at( index );
        result = QPair< QString, QString >{ name, optionValue( name )};
    }
    return result;
}

ParamType ChoiceParam::type() const
{
    return ParamType::Choice;
}

QVariant ChoiceParam::value() const
{
    return QVariant{ m_data->m_index };
}

void ChoiceParam::setValue( const QVariant &value )
{
    bool ok = false;
    int val = value.toInt( &ok );
    if( ok && val >= 0 ) {
        m_data->m_index = val;
    }
}

int ChoiceParam::defaultIndex() const
{
    return m_data->m_defaultIndex;
}

void ChoiceParam::setDefaultIndex( int defaultIndex )
{
    m_data->m_defaultIndex = defaultIndex;
}

int ChoiceParam::numOption() const
{
    return m_data->m_choices.size();
}

}
