#include <memory>

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QIcon>
#include <QWidget>

#include <common/iconstore/IconFontStore.h>

#include <base/explorer/FileHandlerInfo.h>

#include "MonacoEditor.h"
#include "FileHandlerProvider.h"

namespace Quartz { namespace Ext { namespace WebTech {

const QString FileHandlerProvider::EXTENSION_ID{"qzp.webtech.fhandlers"};
const QString FileHandlerProvider::EXTENSION_NAME{"WebTech Based Handlers"};

FileHandlerProvider::FileHandlerProvider()
    : AbstractFileHandlerProvider(EXTENSION_ID, EXTENSION_NAME)
{

}

QVector<std::shared_ptr<FileHandlerInfo>> FileHandlerProvider::handlerInfos()
{
    QVector<std::shared_ptr<FileHandlerInfo>> infos;
    auto fhi = std::make_shared<FileHandlerInfo>(
                    QObject::tr("Monaco Editor"),
                    Quartz::FileHandlerType::Editor,
                    MonacoEditor::extension(),
                    getIcon(FAIcon::PencilAlt),
                    [](QWidget *parent) -> AbstractFileHandler * {
                        return new MonacoEditor(parent);
                    }
                );
    infos.append(fhi);
    return infos;
}


} } }
