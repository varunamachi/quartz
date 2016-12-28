
#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class ContentWidget;

class QUARTZ_BASE_API AbstractContentProvider : public AbstractPlugin
{
public:
    AbstractContentProvider( const QString &pluginId,
                             const QString &pluginName );

    virtual ~AbstractContentProvider();

    virtual QVector< ContentWidget *> widgets() = 0;

    static const QString PLUGIN_TYPE;

private:
};

}
