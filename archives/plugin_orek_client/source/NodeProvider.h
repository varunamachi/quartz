#pragma once

#include <base/general_selector/AbstractGeneralNodeProvider.h>

namespace Quartz { namespace Ext { namespace Orek {

class NodeProvider : public AbstractGeneralNodeProvider
{
public:
    NodeProvider();

    ~NodeProvider();

    bool init();

    bool destroy();

    QVector< std::shared_ptr< NodeInfo >> nodes() const;

    static const QString EXTENSION_ID;

    static const QString EXTENSION_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
