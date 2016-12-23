#pragma once

#include <memory>

class QString;

namespace Quartz {

class QzAppContext;
class AbstractPluginBundle;
class BundleEnv;
namespace Logger {
    class Logger;
}

namespace Plugin {

class BundleContext
{
public:
    ~BundleContext();

    QzAppContext * appContext() const;

    AbstractPluginBundle * pluginBundle() const;

    BundleEnv * bundleEnv() const;

    static void destroy();

    static void init( std::unique_ptr< AbstractPluginBundle > pluginBundle,
                      std::unique_ptr< BundleEnv > env,
                      QzAppContext *appContext );

    static BundleContext * instance();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

    static std::unique_ptr< BundleContext > s_instance;

    BundleContext( std::unique_ptr< AbstractPluginBundle > pluginBundle,
                   std::unique_ptr< BundleEnv > env,
                   QzAppContext *appContext );
};

}

}


inline Quartz::Plugin::BundleContext * bundleContext()
{
    return Quartz::Plugin::BundleContext::instance();
}

inline Quartz::QzAppContext * appContext()
{
    return Quartz::Plugin::BundleContext::instance()->appContext();
}

inline Quartz::BundleEnv * bundleEnv()
{
    return Quartz::Plugin::BundleContext::instance()->bundleEnv();
}

inline Quartz::AbstractPluginBundle * pluginBundle()
{
    return bundleContext()->pluginBundle();
}
