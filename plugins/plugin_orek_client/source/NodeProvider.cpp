#include <base/selector/Node.h>

#include "NodeProvider.h"

namespace Quartz { namespace OrekClient {

using NodeList = QVector< std::shared_ptr< NodeInfo >>;

const QString NodeProvider::PLUGIN_ID{ "qzp.orekclient.provider.node" };
const QString NodeProvider::PLUGIN_NAME{ "Orek Client" };

struct NodeProvider::Data
{
    Data()
    {
//        auto path = Quartz::Node::toPath( "Orek" );
        auto nodeInfo = std::make_shared< NodeInfo >( QStringList{},
                                                      "Orek",
                                                      "qzp.orekclient.content",
                                                      QIcon{} );
        m_nodes.append( nodeInfo );
    }

    NodeList m_nodes;
};

NodeProvider::NodeProvider()
    : AbstractGeneralNodeProvider{ PLUGIN_ID, PLUGIN_NAME }
    , m_data( new Data{} )
{

}

NodeProvider::~NodeProvider()
{

}

bool NodeProvider::init()
{
    return false;
}

bool NodeProvider::destroy()
{
    return false;
}

NodeList NodeProvider::nodes() const
{
    return m_data->m_nodes;
}


} }
