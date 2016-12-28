#pragma once

#include "../QuartzBase.h"
#include "../general_selector/AbstractGeneralNodeProvider.h"

class AbstractConfigPage;

namespace Quartz {

class QUARTZ_BASE_API AbstractConfigPageProvider : public AbstractPlugin
{
public:
    AbstractConfigPageProvider( const QString &pluginId,
                                const QString &pluginName );

    ~AbstractConfigPageProvider();

    virtual QVector< AbstractConfigPage *> configPages() const = 0;

    static const QString PLUGIN_TYPE;

private:

};



}
