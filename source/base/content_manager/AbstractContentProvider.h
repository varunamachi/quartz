
#include <core/ext/Extension.h>

#include "../QuartzBase.h"

namespace Quartz {

class ContentWidget;

class QUARTZ_BASE_API AbstractContentProvider : public Ext::Extension
{
public:
    AbstractContentProvider( const QString &pluginId,
                             const QString &pluginName );

    virtual ~AbstractContentProvider();

    virtual QVector< ContentWidget *> widgets() = 0;

    static const QString EXTENSION_TYPE;

private:
};

}
