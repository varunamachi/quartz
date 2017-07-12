
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QVariant>

#include "Variable.h"
#include "Template.h"

namespace Quartz { namespace Plugin { namespace Creator {

const Variable Template::EMPTY_VARIABLE{ "", "", "", nullptr, false };

struct Template::Data
{
    Data( const QString &name,
          const QString &content )
        : m_name{ name }
        , m_content{ content }
        , m_selected( false )
    {

    }

    QString m_name;

    QString m_content;

    bool m_selected;

    QVector< std::shared_ptr< Variable >> m_vars;
};



Template::Template( const QString &name,
                    const QString &content )
    : m_data{ new Data{ name, content }}
{

}

Template::~Template()
{

}

QString Template::name() const
{
    return m_data->m_name;
}

void Template::addVariable( const QString &key,
                            const QString &value,
                            const QString &description )
{
    m_data->m_vars.push_back(
                std::make_shared< Variable >(
                    key,
                    value ,
                    description,
                    this,
                    m_data->m_selected ));
}

const Variable & Template::variable( const QString &key ) const
{
    for( auto i = 0; i < m_data->m_vars.size(); ++ i ) {
        auto &var = m_data->m_vars.at( i );
        if( var->name() == key ) {
            return *var;
        }
    }
    return EMPTY_VARIABLE;
}

const Variable & Template::variableAt( int index ) const
{
    if( index < m_data->m_vars.size() ) {
        return *m_data->m_vars.at( index );
    }
    return EMPTY_VARIABLE;
}

const QString & Template::content() const
{
    return m_data->m_content;
}

int Template::numChildren() const
{
    if( m_data->m_selected ) {
        return m_data->m_vars.size();
    }
    return 0;
}

int Template::numFields() const
{
    return 2;
}

ITreeNode *Template::child( int row ) const
{
    if( row < m_data->m_vars.size() ) {
        return m_data->m_vars.at( row ).get();
    }
    return nullptr;
}

QVariant Template::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_selected;
    case 1: return m_data->m_name;
    case 2: return m_data->m_vars.size();
    }
    return QVariant{};
}

void Template::setSelected( bool value )
{
    m_data->m_selected = value;
    //Set the value for children
    for( auto i = 0; i < m_data->m_vars.size(); ++ i ) {
        auto var = m_data->m_vars.at( i ).get();
        var->setSelected( value );
    }
}

bool Template::isSelected() const
{
    return m_data->m_selected;
}

ITreeNode * Template::parent() const
{
    return nullptr;
}

int Template::indexOfChild( const ITreeNode *child ) const
{
    int index = -1;
    for( int i = 0; i < m_data->m_vars.size(); ++ i ) {
        if( child == m_data->m_vars.at( i ).get() ) {
            index = i;
            break;
        }
    }
    return index;
}


} } }
