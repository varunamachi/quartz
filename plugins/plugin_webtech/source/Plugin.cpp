

#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "Plugin.h"
#include "FileHandlerProvider.h"
#include "conf/ConfigPageProvider.h"

namespace Quartz { namespace Ext { namespace WebTech {

const QString Plugin::PLUGIN_ID{"qzp.webtech"};
const QString Plugin::PLUGIN_NAME{"WebTech"};

struct Plugin::Data {
    AdapterList m_adapters;
    ExtensionList m_extensions;
    DependencyList m_dependencies;
};

Plugin::Plugin()
    : Quartz::Ext::Plugin(PLUGIN_ID, PLUGIN_NAME)
    , m_data(std::make_unique<Data>()) {
    m_data->m_extensions.append(std::make_shared<FileHandlerProvider>());
    m_data->m_extensions.append(std::make_shared<ConfigPageProvider>());
}

Plugin::~Plugin() {
}

const ExtensionList& Plugin::extensions() const {
    return m_data->m_extensions;
}

const DependencyList& Plugin::dependencies() const {
    return m_data->m_dependencies;
}

const AdapterList& Plugin::adapters() const {
    return m_data->m_adapters;
}

}}} // namespace Quartz::Ext::WebTech
