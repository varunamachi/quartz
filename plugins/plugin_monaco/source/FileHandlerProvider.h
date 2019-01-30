#include <base/explorer/FileHandlerProvider.h>

namespace Quartz { namespace Ext { namespace Monaco {

class FileHandlerProvider : public Quartz::FileHandlerProvider
{
public:
    FileHandlerProvider();

    QVector<std::shared_ptr<FileHandlerInfo> > handlerInfos() override;

    static const QString EXTENSION_ID;
    static const QString EXTENSION_NAME;
};

} } }
