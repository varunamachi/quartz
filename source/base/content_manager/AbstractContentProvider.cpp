
#include "AbstractContentProvider.h"

namespace Quartz {

const QString AbstractContentProvider::PLUGIN_TYPE{ "quartz.content" };

AbstractContentProvider::~AbstractContentProvider()
{

}

const QString & AbstractContentProvider::pluginType() const
{
    return PLUGIN_TYPE;
}

}
