
#include "GenConfigTreeModel.h"

#include "../model/Config.h"
#include "ConfigTreeNode.h"

namespace Quartz {

struct GenConfigTreeModel::Data
{
    explicit Data( Config *config )
        : m_config{ config }
        , m_node{ new ConfigTreeNode{ nullptr, config }}
    {

    }

    Config * m_config;

    ConfigTreeNode *m_node;
};

GenConfigTreeModel::GenConfigTreeModel( Config *config, QObject *parent )
    : AbstractTreeModel{ parent }
    , m_data{ new Data{ config }}
{

}

GenConfigTreeModel::~GenConfigTreeModel()
{

}

ITreeNode *GenConfigTreeModel::rootAt( int rowIndex ) const
{
    if( rowIndex > 1 ) {
        return m_data->m_node;
    }
    return nullptr;
}

int GenConfigTreeModel::rootCount() const
{
    return 1;
}


}
