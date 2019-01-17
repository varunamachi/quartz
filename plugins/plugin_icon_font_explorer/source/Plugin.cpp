
#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "Plugin.h"
#include "NodeProvider.h"
#include "ContentProvider.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

const QString Plugin::PLUGIN_ID{ "qzplugin.icon_font_explorer" };
const QString Plugin::PLUGIN_NAME{ "Icon Font Explorer " };

struct Plugin::Data
{
    AdapterList m_adapters;
    ExtensionList m_extensions;
    DependencyList m_dependencies;
};

Plugin::Plugin()
    : Quartz::Ext::Plugin(PLUGIN_ID, PLUGIN_NAME)
    , m_data(std::make_unique<Data>())
{
    auto np = std::make_shared<NodeProvider>();
    auto cp = std::make_shared<ContentProvider>();
    m_data->m_extensions << np << cp;
}

Plugin::~Plugin()
{

}

const ExtensionList & Plugin::extensions() const
{
    return m_data->m_extensions;
}


const DependencyList & Plugin::dependencies() const
{
    return m_data->m_dependencies;
}

const AdapterList & Plugin::adapters() const
{
    return m_data->m_adapters;
}


} } }
            
