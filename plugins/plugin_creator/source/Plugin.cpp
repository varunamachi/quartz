#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "ContentProvider.h"
#include "NodeProvider.h"
#include "Plugin.h"
#include "TemplateManager.h"

namespace Quartz { namespace Ext { namespace Creator {

const QString Plugin::PLUGIN_ID{ "qzplugin.creator" };
const QString Plugin::PLUGIN_NAME("Creator");

struct Plugin::Data
{
    AdapterList m_adapters;

    ExtensionList m_plugins;

    DependencyList m_dependencies;
};

Plugin::Plugin()
    : Quartz::Ext::Plugin(PLUGIN_ID, PLUGIN_NAME)
    , m_data{ new Data{} }
{
    auto np = std::make_shared<NodeProvider>() ;
    auto tman = std::make_shared<TemplateManager>();
    auto cp = std::make_shared<ContentProvider>(tman);

    m_data->m_plugins.push_back(np);
    m_data->m_plugins.push_back(cp);
    m_data->m_adapters.push_back(tman);
}

Plugin::~Plugin()
{

}

const ExtensionList & Plugin::extensions() const
{
    return m_data->m_plugins;
}


const DependencyList & Plugin::dependencies() const
{
    return m_data->m_dependencies;
}

const AdapterList &Plugin::adapters() const
{
    return m_data->m_adapters;
}


} } }
