#include "NodeProvider.h"

namespace Quartz { namespace OrekClient {

bool NodeProvider::init()
{
    return false;
}

bool NodeProvider::destroy()
{
    return false;
}

QVector< std::shared_ptr< NodeInfo >> NodeProvider::nodes() const
{
    return QVector< std::shared_ptr< NodeInfo >>{ };
}


} }
