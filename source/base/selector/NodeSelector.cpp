
#include <QVBoxLayout>
#include "NodeSelector.h"

namespace Quartz {


struct NodeSelector::Data
{

};

const QString NodeSelector::SELECTOR_ID{ "quartz.node_selector" };
const QString NodeSelector::SELECTOR_NAME{ "Pages" };
const QString NodeSelector::ADAPTER_NAME{ "Node Selector" };
const QString NodeSelector::PLUGIN_TYPE{ "quartz.node" };

NodeSelector::NodeSelector( QWidget *parent )
    : AbstractSelector( SELECTOR_ID,
                        SELECTOR_NAME,
                        parent )
{

}

NodeSelector::~NodeSelector()
{

}

const QString &NodeSelector::pluginType() const
{
    return  PLUGIN_TYPE;
}

const QString &NodeSelector::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool NodeSelector::handlePlugin( IPlugin *plugin )
{
    return false;
}

bool NodeSelector::finalizePlugins()
{
    return false;
}

void NodeSelector::setupLayout()
{

}

QModelIndex NodeSelector::index( int row,
                                 int column,
                                 const QModelIndex &parent ) const
{
    return QModelIndex{ };
}

QModelIndex NodeSelector::parent( const QModelIndex &child ) const
{
    return QModelIndex{ };
}

int NodeSelector::rowCount( const QModelIndex &parent ) const
{
    return 0;
}

int NodeSelector::columnCount( const QModelIndex &parent ) const
{
    return 0;
}

QVariant NodeSelector::data( const QModelIndex &index, int role ) const
{
    return QVariant{ };
}

}
