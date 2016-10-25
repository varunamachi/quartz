#include <QHash>


#include "ContentWidget.h"
#include "AbstractContentProvider.h"
#include "ContentManager.h"

namespace Quartz {

struct ContentManager::Data
{
    QHash< QString, QWidget *> m_contentWidgets;

    QHash< QString, QWidget *> m_pluginWidgets;
};

const QString ContentManager::ADAPTER_NAME{ "Content Manager" };






const QString & ContentManager::pluginType() const
{
    return AbstractContentProvider::PLUGIN_TYPE;
}

const QString & ContentManager::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ContentManager::handlePlugin(IPlugin *plugin)
{
    return false;
}

bool ContentManager::finalizePlugins()
{
    return false;
}


}
