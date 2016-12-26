#pragma once

#include "../QuartzBase.h"
#include "../general_selector/AbstractGeneralNodeProvider.h"

namespace Quartz {

class QUARTZ_BASE_API AbstractConfigNodeProvider : public AbstractPlugin
{
public:
    AbstractConfigNodeProvider( const QString &pluginId,
                                const QString &pluginName,
                                const QStringList &dependencies );

    ~AbstractConfigNodeProvider();

    virtual QVector< std::shared_ptr< NodeInfo >> nodes() const = 0;

    static const QString PLUGIN_TYPE;

private:

};



}
