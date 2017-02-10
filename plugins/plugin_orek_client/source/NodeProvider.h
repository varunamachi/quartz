#pragma once

#include <base/general_selector/AbstractGeneralNodeProvider.h>

namespace Quartz { namespace OrekClient {

class NodeProvider : public AbstractGeneralNodeProvider
{
public:
    NodeProvider();

    ~NodeProvider();

    bool init();

    bool destroy();

    QVector< std::shared_ptr< NodeInfo >> nodes() const;

    static const QString PLUGIN_ID;

    static const QString PLUGIN_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} }
