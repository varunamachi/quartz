#pragma once

#include <memory>


#include <core/extension_system/AbstractPlugin.h>

namespace Quartz { namespace Plugin { namespace Creator {

class Template;

class AbstractTemplateProvider : public AbstractPlugin
{
public:
    AbstractTemplateProvider( const QString &pluginID,
                              const QString &pluginName );

    ~AbstractTemplateProvider();

    virtual QList< std::shared_ptr< Template >> templates() const = 0;

    static const QString PLUGIN_TYPE;


private:
};

} } }
