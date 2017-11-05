
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

    std::unique_ptr< ConfigTreeNode > m_node;
};

GenConfigTreeModel::GenConfigTreeModel( Config *config, QObject *parent )
    : AbstractTreeModel{ parent }
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
    m_data->m_node = std::unique_ptr< ConfigTreeNode >{
            new ConfigTreeNode{ nullptr, config }};
    endResetModel();

}

ITreeNode *GenConfigTreeModel::rootAt( int /*rowIndex*/ ) const
{
    return m_data->m_node.get();
}

int GenConfigTreeModel::rootCount() const
{
    return m_data->m_node->numChildren() != 0 ? 1 : 0;
}


}
