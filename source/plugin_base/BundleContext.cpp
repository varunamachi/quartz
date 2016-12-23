
#include "BundleContext.h"

#include <core/extension_system/AbstractPluginBundle.h>
#include <core/extension_system/BundleEnv.h>
#include <base/QzAppContext.h>

namespace Quartz { namespace Plugin {


struct BundleContext::Data {
    Data( std::unique_ptr< AbstractPluginBundle > bundle,
          std::unique_ptr< BundleEnv > env,
          QzAppContext *appContext )
        : m_bundle( std::move( bundle ))
        , m_bundleEnv{ std::move( env )}
        , m_appContext{  appContext }
    {

    }

    std::unique_ptr< AbstractPluginBundle > m_bundle;

    std::unique_ptr< BundleEnv > m_bundleEnv;

    QzAppContext *m_appContext;

};

std::unique_ptr< BundleContext > BundleContext::s_instance{ nullptr };

BundleContext::~BundleContext()
{
    m_data->m_bundle = nullptr;
    m_data->m_bundleEnv.reset();
    m_data->m_appContext = nullptr;
}


QzAppContext *BundleContext::appContext() const
{
    return m_data->m_appContext;
}

AbstractPluginBundle *BundleContext::pluginBundle() const
{
    return m_data->m_bundle.get();
}

void BundleContext::destroy()
{
    s_instance.release();
}

void BundleContext::init( std::unique_ptr< AbstractPluginBundle > bundle,
                          std::unique_ptr< BundleEnv > env,
                          QzAppContext *appContext )
{
    s_instance = std::unique_ptr< BundleContext >{
            new BundleContext{ std::move( bundle ),
                               std::move( env ),
                               appContext }};
}

BundleContext *BundleContext::instance()
{
    return s_instance.get();
}

BundleContext::BundleContext( std::unique_ptr< AbstractPluginBundle > bundle,
                              std::unique_ptr< BundleEnv > env,
                              QzAppContext *appContext )
    : m_data{ new Data{ std::move( bundle ),
                        std::move( env ),
                        appContext }}
{

}


} }
