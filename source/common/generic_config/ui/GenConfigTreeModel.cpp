
#include "GenConfigTreeModel.h"

#include "../model/Config.h"

namespace Quartz {


const QVector< QString > HEADERS{
    QObject::tr( "Name" ),
    QObject::tr( "Value" )
};

struct GenConfigTreeModel::Data
{
    explicit Data( Config *config )
        : m_config{ config }
    {

    }

    Config * m_config;

};

GenConfigTreeModel::GenConfigTreeModel( Config *config, QObject *parent )
    : AbstractTreeModel{
          parent,
          AbstractTreeModel::Options{ 2, false, false, HEADERS }}
    , m_data{ new Data{ config }}
{

}

GenConfigTreeModel::~GenConfigTreeModel()
{

}

void GenConfigTreeModel::setConfig( Config *config )
{
    beginResetModel();
    m_data->m_config = config;
    endResetModel();

}

TreeNode *GenConfigTreeModel::rootAt( int /*rowIndex*/ ) const
{
    return m_data->m_config;
}

int GenConfigTreeModel::rootCount() const
{
    return m_data->m_config->numChildren() != 0 ? 1 : 0;
}


}
