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

namespace Quartz { namespace Ext { namespace Monaco {

const QString FileHandlerProvider::EXTENSION_ID{"qzp.editor.monaco"};
const QString FileHandlerProvider::EXTENSION_NAME{"Monaco Editor"};

FileHandlerProvider::FileHandlerProvider()
    : AbstractFileHandlerProvider(EXTENSION_ID, EXTENSION_NAME)
{

}

QVector<std::shared_ptr<FileHandlerInfo>> FileHandlerProvider::handlerInfos()
{
    auto extns = QStringList{
            "json",
            "txt",
            "ts",
            "js",
            "cpp",
            "dart",
    };
    QVector<std::shared_ptr<FileHandlerInfo>> infos;
    auto fhi = std::make_shared<FileHandlerInfo>(
                    QObject::tr("Monaco Editor"),
                    Quartz::FileHandlerType::Editor,
                    extns,
                    getIcon(FAIcon::PencilAlt),
                    [](QWidget *parent) -> AbstractFileHandler * {
                        return new MonacoEditor(parent);
                    }
                );
    infos.append(fhi);
    return infos;
}


} } }
