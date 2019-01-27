#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QStandardPaths>


#include <common/editor/MonacoEditor.h>
#include <common/iconstore/IconFontStore.h>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"
#include "FileSystemSelector.h"
#include "FileHandlerManager.h"

namespace Quartz {

const QString FileSystemSelector::SELECTOR_ID{ "qz.fs_selector" };
const QString FileSystemSelector::SELECTOR_NAME("Explore");

struct FileSystemSelector::Data
{
    explicit Data(QWidget *parent)
        : m_fsModel(new QFileSystemModel(parent))
        , m_fsView(new QTreeView(parent))
        //        , m_editor(new MonacoEditor(parent))
    {
        auto home =
                QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        m_fsModel->setRootPath(home);
        m_fsView->setModel(m_fsModel);
        m_fsView->setRootIndex(m_fsModel->index(home));
        for (int i = 1; i < m_fsModel->columnCount(); ++i) {
            m_fsView->hideColumn(i);
        }
    }

    QFileSystemModel *m_fsModel;

    QTreeView *m_fsView;

    MonacoEditor *m_editor;

};

FileSystemSelector::FileSystemSelector(QWidget *parent)
    : AbstractSelector(
          SELECTOR_ID,
          SELECTOR_NAME,
          getNormalIcon(FAIcon::Folder),
          getActiveIcon(FAIcon::Folder),
          parent)
    , m_data(std::make_unique<Data>(this))
{
    auto lyt = new QVBoxLayout();
    lyt->addWidget(m_data->m_fsView);
    this->setLayout(lyt);

    lyt->setContentsMargins({});
    m_data->m_fsView->setContentsMargins({});
    this->setContentsMargins({});

    connect(m_data->m_fsView,
            &QTreeView::doubleClicked,
            [this](const QModelIndex &index) {
        auto path = m_data->m_fsModel->filePath(index);
        appContext()->contentManager()->selectContent(
                    FileHandlerManager::CONTENT_ID);
        auto page = appContext()->contentManager()->content(
                    FileHandlerManager::CONTENT_ID);
        auto fhMan = qobject_cast<FileHandlerManager *>(page);
        if (fhMan != nullptr) {
            fhMan->handle(path);
        }
    });
}

FileSystemSelector::~FileSystemSelector()
{

}

void FileSystemSelector::selected()
{
    //    m_data->m_fsView->selectionModel()->set

}

void FileSystemSelector::unselected()
{

}

}
