#pragma once

#include <base/selector/AbstractNodeProvider.h>

namespace Quartz { namespace Plugin { namespace Sample {

class NodeProvider : public AbstractNodeProvider
{
public:
    NodeProvider();

    ~NodeProvider();

    bool init() override;

    bool destroy() override;

    std::shared_ptr< NodeInfo > nodeInfo() const override;

    static const QString PLUGIN_ID;

    static const QString PLUGIN_NAME;

    static const QStringList DEPENDENCIES;
};


} } }
