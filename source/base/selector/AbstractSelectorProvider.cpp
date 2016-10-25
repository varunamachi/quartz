
#include "AbstractSelectorProvider.h"

namespace Quartz {

const QString AbstractSelectorProvider::PLUGIN_TYPE{ "quartz.selector" };

AbstractSelectorProvider::~AbstractSelectorProvider()
{

}

const QString & AbstractSelectorProvider::pluginType() const
{
    return PLUGIN_TYPE;
}

}
