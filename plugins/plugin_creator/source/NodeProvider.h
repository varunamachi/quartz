#pragma once

#include <base/general_selector/AbstractGeneralNodeProvider.h>

namespace Quartz { namespace Ext { namespace Creator {

class NodeProvider : public AbstractGeneralNodeProvider
{
public:
    NodeProvider();

    ~NodeProvider();

    bool init() override;

    bool destroy() override;

    QVector<std::shared_ptr<NodeInfo>> nodes() const override;

    static const QString EXTENSION_ID;

    static const QString EXTENSION_NAME;
};


} } }
