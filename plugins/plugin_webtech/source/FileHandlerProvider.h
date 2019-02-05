#include <base/explorer/AbstractFileHandlerProvider.h>

namespace Quartz { namespace Ext { namespace WebTech {

class FileHandlerProvider : public AbstractFileHandlerProvider
{
public:
    FileHandlerProvider();

    QVector<std::shared_ptr<FileHandlerInfo> > handlerInfos() override;

    static const QString EXTENSION_ID;
    static const QString EXTENSION_NAME;
};

} } }
