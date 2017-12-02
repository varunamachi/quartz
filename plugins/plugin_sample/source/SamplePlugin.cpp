#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "ViewProvider.h"
#include "ContentProvider.h"
#include "NodeProvider.h"
#include "TitleItemProvider.h"
#include "SamplePlugin.h"

namespace Quartz { namespace Ext { namespace Sample {

const QString SamplePlugin::PLUGIN_ID{ "qzplugin.sample" };
const QString SamplePlugin::PLUGIN_NAME{ "Sample Plugin" };

struct SamplePlugin::Data
{
    AdapterList m_adapters;
    ExtensionList m_plugins;
    DependencyList m_dependencies;

};

SamplePlugin::SamplePlugin()
    : Quartz::Ext::Plugin{ PLUGIN_ID, PLUGIN_NAME }
    , m_data{ new Data{} }
{

#ifdef QT_DEBUG
    m_data->m_plugins.push_back( std::make_shared< ViewProvider >() );
    m_data->m_plugins.push_back( std::make_shared< ContentProvider >() );
    m_data->m_plugins.push_back( std::make_shared< NodeProvider >() );
    m_data->m_plugins.push_back( std::make_shared< TitleItemProvider >() );
#endif
}

SamplePlugin::~SamplePlugin()
{

}

const ExtensionList & SamplePlugin::extensions() const
{
    return m_data->m_plugins;
}


const DependencyList & SamplePlugin::dependencies() const
{
    return m_data->m_dependencies;
}

const AdapterList &SamplePlugin::adapters() const
{
    return m_data->m_adapters;
}


} } }
