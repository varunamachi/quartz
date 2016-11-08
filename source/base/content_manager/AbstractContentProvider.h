
#include <core/extension_system/IPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class ContentWidget;

class QUARTZ_BASE_API AbstractContentProvider : public IPlugin
{
public:
    virtual ContentWidget * widget() = 0;

    virtual ~AbstractContentProvider();

    const QString & pluginType() const;

    static const QString PLUGIN_TYPE;

private:
};

}
