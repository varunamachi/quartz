
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QVariant>

#include "Variable.h"
#include "Template.h"
#include "TemplateInstance.h"

namespace Quartz { namespace Plugin { namespace Creator {

const Variable Template::EMPTY_VARIABLE{ "", "", "" };

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

    QVector< std::shared_ptr< TemplateInstance >> m_instances;
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
                    description ));
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
        return m_data->m_instances.size();
    }
    return 0;
}

int Template::numFields() const
{
    return 2;
}

ITreeNode *Template::child( int row ) const
{
    if( row < m_data->m_instances.size() ) {
        return m_data->m_instances.at( row ).get();
    }
    return nullptr;
}

QVariant Template::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_selected;
    case 1: return m_data->m_name;
    case 2: return m_data->m_instances.size();
    }
    return QVariant{};
}

void Template::setSelected( bool value )
{
    m_data->m_selected = value;
    //Set the value for children
    for( auto i = 0; i < m_data->m_instances.size(); ++ i ) {
        auto ins = m_data->m_instances.at( i ).get();
        ins->setSelected( value );
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
    for( int i = 0; i < m_data->m_instances.size(); ++ i ) {
        if( child == m_data->m_instances.at( i ).get() ) {
            index = i;
            break;
        }
    }
    return index;
}

bool Template::isEditable( int /*column*/ ) const
{
    return false;
}

void Template::setData( int /*column*/, const QVariant &/*data*/ )
{
    //Nothing to set
}

void Template::addChild( std::shared_ptr< ITreeNode > child )
{
    //Check if already exists
    auto templateInsace = std::dynamic_pointer_cast<
            TemplateInstance >( child );
    if( templateInsace ) {
        m_data->m_instances.push_back( templateInsace );
    }
}

void Template::removeChild( const ITreeNode *child )
{
    if( child == nullptr ) {
        return;
    }
    for( auto i = m_data->m_instances.size() - 1; i <= 0 ; i -- ) {
        const auto &ins = m_data->m_instances.at( i );
        if( ins.get() == child ) {
            m_data->m_instances.remove( i );
        }
    }
}

} } }
