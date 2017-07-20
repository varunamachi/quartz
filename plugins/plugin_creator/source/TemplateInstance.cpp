#include <QString>
#include <QVariant>

#include "Template.h"
#include "TemplateInstance.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateInstance::Data
{
    Data( const QString &name,
          Template *parent )
     : m_name{ name }
     , m_parent{ parent }
     , m_selected{ true }
    {

    }

    QString m_name;

    Template *m_parent;

    bool m_selected;

};

TemplateInstance::TemplateInstance( const QString &name,
                                    Template *parent  )
    : m_data{ new Data{ name, parent }}
{

}

TemplateInstance::~TemplateInstance()
{

}

const QString & TemplateInstance::name() const
{
    return m_data->m_name;
}

int TemplateInstance::numChildren() const
{
    return 0;
}

int TemplateInstance::numFields() const
{
    return 1;
}

ITreeNode * TemplateInstance::child( int /*row*/ ) const
{
    return nullptr;
}

QVariant TemplateInstance::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_name;
    }
    return "";
}

void TemplateInstance::setSelected( bool value )
{
    m_data->m_selected = value;
}

bool TemplateInstance::isSelected() const
{
    return m_data->m_selected;
}

ITreeNode *TemplateInstance::parent() const
{
    return m_data->m_parent;
}

int TemplateInstance::indexOfChild( const ITreeNode */*child*/ ) const
{
    //There are no children of TemplateInstance, hence -1
    return -1;
}

bool TemplateInstance::isEditable( int column ) const
{
    return column == 0;
}

void TemplateInstance::setData( int column, const QVariant &data )
{
    if( column == 0 ) {
        m_data->m_name= data.toString();
    }
}

void TemplateInstance::addChild( std::shared_ptr< ITreeNode > /*child*/ )
{
    //nothing
}

void TemplateInstance::removeChild( const ITreeNode */*child*/ )
{
    //nothing
}


} } }
