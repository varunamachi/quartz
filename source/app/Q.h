#pragma once

#include <memory>



namespace Quartz {

class ThemeManager;
class PluginManager;
class JobManager;

class Q
{
public:

    ~Q();

    static Q & get();

    static void init(std::unique_ptr<ThemeManager> themeManager,
                      std::unique_ptr<PluginManager> pluginManager,
                      std::unique_ptr<JobManager> jobManager);

    ThemeManager & themeManager();

    PluginManager & pluginManager();

    JobManager & jobManager();

private:
    struct Data;
    std::unique_ptr<Data> m_data;

    Q(std::unique_ptr<ThemeManager> themeManager,
       std::unique_ptr<PluginManager> pluginManager,
       std::unique_ptr<JobManager> jobManager);


    static Q *s_instance;

    std::unique_ptr<ThemeManager> m_themeManager;
};


}
