
#include <base/selector/Node.h>

#include "NodeProvider.h"
#include "MainWidget.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

const QString NodeProvider::PLUGIN_ID{
    "qzp.serial_console.provider.node" };
const QString NodeProvider::PLUGIN_NAME{
    "Serial Console Node" };

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
    auto nodeInfo = std::make_shared< NodeInfo >(
                QStringList{},
                "Serial Console",
                MainWidget::CONTENT_ID,
                QIcon{} );
    QVector< std::shared_ptr< NodeInfo >> nodes;
    nodes.push_back( nodeInfo );
    return nodes;
}

} } }
