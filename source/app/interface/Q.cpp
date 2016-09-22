
#include <core/extension_system/PluginManager.h>
#include <core/job_manager/JobManager.h>

#include "../theme/ThemeManager.h"
#include "Q.h"

namespace Quartz {

Q * Q::s_instance = nullptr;

struct Q::Data
{
    Data( std::unique_ptr< ThemeManager > themeManager,
          std::unique_ptr< PluginManager > pluginManager,
          std::unique_ptr< JobManager > jobManager )
        : m_themeManager( std::move( themeManager ))
        , m_pluginManager( std::move( pluginManager ))
        , m_jobManager( std::move( jobManager ))
    {

    }

    ~Data() { }

    std::unique_ptr< ThemeManager > m_themeManager;

    std::unique_ptr< PluginManager > m_pluginManager;

    std::unique_ptr< JobManager > m_jobManager;
};


Q::~Q()
{

}

Q & Q::get()
{
    return *s_instance;
}


void Q::init( std::unique_ptr< ThemeManager > themeManager,
              std::unique_ptr< PluginManager > pluginManager,
              std::unique_ptr< JobManager > jobManager )
{
    s_instance = new Q( std::move( themeManager ),
                        std::move( pluginManager ),
                        std::move( jobManager ));
}

Q::Q( std::unique_ptr<ThemeManager> themeManager,
      std::unique_ptr<PluginManager> pluginManager,
      std::unique_ptr<JobManager> jobManager )
    : m_data( std::make_unique< Data >( std::move( themeManager ),
                                        std::move( pluginManager ),
                                        std::move( jobManager )))
{

}

ThemeManager & Q::themeManager()
{
    return *m_data->m_themeManager;
}


PluginManager & Q::pluginManager()
{
    return *m_data->m_pluginManager;
}


JobManager & Q::jobManager()
{
    return *m_data->m_jobManager;
}


}
