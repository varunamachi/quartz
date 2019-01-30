


#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "Plugin.h"
#include "FileHandlerProvider.h"

namespace Quartz { namespace Ext { namespace Monaco {

const QString Plugin::PLUGIN_ID{ "qz.editor.monaco" };
const QString Plugin::PLUGIN_NAME{ "Monaco " };

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
    m_data->m_extensions.append(std::make_shared<FileHandlerProvider>());
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
            
