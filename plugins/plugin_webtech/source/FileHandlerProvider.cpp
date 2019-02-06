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
#include "conf/Conf.h"

namespace Quartz { namespace Ext { namespace WebTech {

const QString FileHandlerProvider::EXTENSION_ID{"qzp.webtech.fhandlers"};
const QString FileHandlerProvider::EXTENSION_NAME{"WebTech Based Handlers"};

auto createEditor(QWidget *parent) -> AbstractFileHandler * {
    auto editor = new MonacoEditor(parent);
    editor->setTheme(conf<QString>(Conf::EDITOR_THEME, "vs-dark"));
    editor->setRulerAt(conf<int>(Conf::EDITOR_VLINE_NUM, 80));
    editor->showMinimap(conf<bool>(Conf::EDITOR_SHOW_MINIMAP, false));
    editor->showLineNumber(conf<bool>(Conf::EDITOR_SHOW_LINENUM, true));
    return editor;
}

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
                    &createEditor
                );
    infos.append(fhi);
    return infos;
}


} } }
