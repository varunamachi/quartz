

#include <common/iconstore/IconFontStore.h>

#include <base/selector/Node.h>

#include "NodeProvider.h"
#include "MainWidget.h"


namespace Quartz { namespace Ext { namespace IconFontExplorer {

const QString NodeProvider::EXTENSION_ID{
    "qzp.icon_font_explorer.provider.node" };
const QString NodeProvider::EXTENSION_NAME{
    "Quartz Icon Font Explorer  Node" };

NodeProvider::NodeProvider()
    : AbstractGeneralNodeProvider(EXTENSION_ID, EXTENSION_NAME)
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

QVector<std::shared_ptr<NodeInfo>> NodeProvider::nodes() const
{
    auto nodeInfo = std::make_shared<NodeInfo>(
                QStringList{},
                "Icon Fonts",
                MainWidget::CONTENT_ID,
                getIcon(FAIcon::Font));
    QVector<std::shared_ptr<NodeInfo>> nodes;
    nodes.push_back(nodeInfo);
    return nodes;
}

} } }


            
