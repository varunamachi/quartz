#include <QFileSystemModel>
#include <QTreeView>

#include <common/widgets/MonacoEditor.h>

#include "EditorManager.h"

namespace Quartz {

struct EditorManager::Data
{
    explicit Data(QWidget *parent)
    {

    }

};

EditorManager::EditorManager(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
}

EditorManager::~EditorManager()
{

}

}
