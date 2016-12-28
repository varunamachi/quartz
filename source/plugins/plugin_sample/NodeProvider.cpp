
#include <base/selector/Node.h>

#include "NodeProvider.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString NodeProvider::PLUGIN_ID{
    "qzp.sample.provider.node" };
const QString NodeProvider::PLUGIN_NAME{
    "Quartz Sample Node" };
const QStringList NodeProvider::DEPENDENCIES{ };

NodeProvider::NodeProvider()
    : AbstractGeneralNodeProvider{ PLUGIN_ID, PLUGIN_NAME, DEPENDENCIES }
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
    auto path = Node::toPath( "Plugin>Sample" );
    auto nodeInfo = std::make_shared< NodeInfo >( path,
                                                  "Sample Node",
                                                  "qzp.sample.content.one",
                                                  QIcon{} );
    QVector< std::shared_ptr< NodeInfo >> nodes;
    nodes.push_back( nodeInfo );
    return nodes;
}

} } }
