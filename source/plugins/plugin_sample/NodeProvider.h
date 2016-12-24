#pragma once

#include <base/general_selector/AbstractGeneralNodeProvider.h>

namespace Quartz { namespace Plugin { namespace Sample {

class NodeProvider : public AbstractGeneralNodeProvider
{
public:
    NodeProvider();

    ~NodeProvider();

    bool init() override;

    bool destroy() override;

    QVector< std::shared_ptr< NodeInfo >> nodes() const override;

    static const QString PLUGIN_ID;

    static const QString PLUGIN_NAME;

    static const QStringList DEPENDENCIES;
};


} } }
