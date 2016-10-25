
#include "AbstractNodeProvider.h"

namespace Quartz {

const QString AbstractNodeProvider::PLUGIN_TYPE{ "quartz.node" };

AbstractNodeProvider::~AbstractNodeProvider()
{

}

const QString &AbstractNodeProvider::pluginType() const
{
    return PLUGIN_TYPE;
}

}
