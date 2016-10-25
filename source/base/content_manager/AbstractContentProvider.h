
#include <core/extension_system/IPlugin.h>


namespace Quartz {

class ContentWidget;

class AbstractContentProvider : public IPlugin
{
public:
    virtual ContentWidget * widget() = 0;

    virtual ~AbstractContentProvider();

    const QString & pluginType() const;

    static const QString PLUGIN_TYPE;

private:
};

}
