
#include <common/iconstore/IconFontStore.h>

#include <base/selector/Node.h>

#include "NodeProvider.h"

namespace Quartz { namespace Ext { namespace Sample {

const QString NodeProvider::EXTENSION_ID{
    "qzp.sample.provider.node" };
const QString NodeProvider::EXTENSION_NAME{
    "Quartz Sample Node" };

NodeProvider::NodeProvider()
    : AbstractGeneralNodeProvider{ EXTENSION_ID, EXTENSION_NAME }
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
    auto nodeInfo = std::make_shared< NodeInfo >(
                path,
                "Sample Node",
                "qzp.sample.content.one",
                getIcon(MatIcon::Gesture));
    QVector< std::shared_ptr< NodeInfo >> nodes;
    nodes.push_back( nodeInfo );
    return nodes;
}

} } }
