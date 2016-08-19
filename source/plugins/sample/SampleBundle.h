#pragma once

#include <QString>

#include <core/PluginBundle.h>




class SampleBundle : public Quartz::PluginBundle
{
public:
    SampleBundle();

    static const QString BUNDLE_ID;

    static const QString BUNDLE_NAME;

private:

};

}
