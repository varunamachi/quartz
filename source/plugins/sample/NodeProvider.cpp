
#include "NodeProvider.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString NodeProvider::PLUGIN_ID{
    "qzplugin.sample.provider.node" };
const QString NodeProvider::PLUGIN_NAME{
    "Quartz Sample Node" };
const QStringList NodeProvider::DEPENDENCIES{ };

NodeProvider::NodeProvider()
    : AbstractNodeProvider{ PLUGIN_ID, PLUGIN_NAME, DEPENDENCIES }
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

std::shared_ptr< NodeInfo > NodeProvider::nodeInfo() const
{
    QStringList path;
    path << "Quartz" << "Quartz";
    auto nodeInfo = std::make_shared< NodeInfo >( QString{ "Content" },
                                                  path,
                                                  QIcon{} );
    return nodeInfo;
}

} } }
