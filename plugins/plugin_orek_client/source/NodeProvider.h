#pragma once

#include <base/general_selector/AbstractGeneralNodeProvider.h>

namespace Quartz { namespace OrekClient {

class NodeProvider : public AbstractGeneralNodeProvider
{
public:
    bool init();

    bool destroy();

    QVector<std::shared_ptr<NodeInfo> > nodes() const;
};

} }
