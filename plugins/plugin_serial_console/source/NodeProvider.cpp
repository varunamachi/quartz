
#include <common/iconstore/IconFontStore.h>

#include <base/selector/Node.h>

#include "NodeProvider.h"
#include "MainWidget.h"

namespace Quartz { namespace Ext { namespace SerialConsole {

const QString NodeProvider::EXTENSION_ID{"qzp.serial_console.provider.node"};
const QString NodeProvider::EXTENSION_NAME{"Serial Console Node"};

NodeProvider::NodeProvider()
    : AbstractGeneralNodeProvider(EXTENSION_ID, EXTENSION_NAME) {
}

NodeProvider::~NodeProvider() {
}

bool NodeProvider::init() {
    return true;
}

bool NodeProvider::destroy() {
    return true;
}

QVector<std::shared_ptr<NodeInfo>> NodeProvider::nodes() const {
    auto nodeInfo = std::make_shared<NodeInfo>(QStringList{},
                                               "Serial Console",
                                               MainWidget::CONTENT_ID,
                                               getIcon(MatIcon::Tv));
    QVector<std::shared_ptr<NodeInfo>> nodes;
    nodes.push_back(nodeInfo);
    return nodes;
}

}}} // namespace Quartz::Ext::SerialConsole
