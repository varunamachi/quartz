
#include <base/selector/Node.h>

#include "NodeProvider.h"

namespace Quartz { namespace Plugin { namespace Creator {

const QString NodeProvider::PLUGIN_ID{
    "qzp.creator.provider.node" };
const QString NodeProvider::PLUGIN_NAME{
    "Quartz Creator Node" };

NodeProvider::NodeProvider()
    : AbstractGeneralNodeProvider{ PLUGIN_ID, PLUGIN_NAME }
{

}

NodeProvider::~NodeProvider()
{

}

bool NodeProvider::init()
{
    return true;
}

bool NodeProvider::destroy()
{
    return true;
}

QVector< std::shared_ptr< NodeInfo >> NodeProvider::nodes() const
{
    auto nodeInfo = std::make_shared< NodeInfo >( QStringList{},
                                                  "Creator",
                                                  "qzp.creator.content.main",
                                                  QIcon{} );
    QVector< std::shared_ptr< NodeInfo >> nodes;
    nodes.push_back( nodeInfo );
    return nodes;
}

} } }
