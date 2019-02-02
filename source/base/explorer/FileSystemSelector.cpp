#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QLineEdit>
#include <QPushButton>
#include <QFileInfo>
#include <QFileDialog>

#include <core/logger/Logging.h>
#include <common/iconstore/IconFontStore.h>
#include <core/app_config/ConfigManager.h>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"
#include "FileSystemSelector.h"
#include "FileHandlerManager.h"

namespace Quartz {

const QString FileSystemSelector::SELECTOR_ID{ "qz.fs_selector" };
const QString FileSystemSelector::SELECTOR_NAME("Explore");
const QString FileSystemSelector::CONFIG_PATH("explorer.path");
const QString FileSystemSelector::CONFIG_RECENT_PATHS("explorer.recent");

struct FileSystemSelector::Data
{
    explicit Data(QWidget *parent)
        : m_fsModel(new QFileSystemModel(parent))
        , m_fsView(new QTreeView(parent))
        , m_pathEdit(new QLineEdit(parent))
        , m_browseButton(new QPushButton(getIcon(FAIcon::File), "", parent))
    {
        m_fsView->setModel(m_fsModel);
        for (int i = 1; i < m_fsModel->columnCount(); ++i) {
            m_fsView->hideColumn(i);
        }
    }

    QFileSystemModel *m_fsModel;

    QTreeView *m_fsView;

    QLineEdit *m_pathEdit;

    QPushButton *m_browseButton;

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

    auto topLayout = new QHBoxLayout();
    topLayout->addWidget(m_data->m_pathEdit);
    topLayout->addWidget(m_data->m_browseButton);
    topLayout->setContentsMargins({5, 0, 0, 0});

    auto lyt = new QVBoxLayout();
    lyt->addLayout(topLayout);
    lyt->addWidget(m_data->m_fsView);
    this->setLayout(lyt);

    lyt->setContentsMargins({});
    m_data->m_fsView->setContentsMargins({});
    this->setContentsMargins({});

    auto home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    auto path = appContext()->configManager()->get<QString>(CONFIG_PATH, home);
    setPath(path);
    m_data->m_pathEdit->setText(path);

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
    connect(m_data->m_browseButton,
            &QPushButton::released,
            [=]() {
        auto dirPath = QFileDialog::getExistingDirectory(
                    this,
                    tr("Explore directory"),
                    m_data->m_pathEdit->text());
        if (! dirPath.isEmpty()) {
            m_data->m_pathEdit->setText(dirPath);
            this->setPath(dirPath);
        }
    });
    connect(m_data->m_pathEdit,
            &QLineEdit::editingFinished,
            [=](){
        const auto &path = m_data->m_pathEdit->text();
        this->setPath(path);
    });
}

FileSystemSelector::~FileSystemSelector()
{

}

void FileSystemSelector::selected()
{
    appContext()->contentManager()->selectContent(
                FileHandlerManager::CONTENT_ID);

}

void FileSystemSelector::unselected()
{

}

void FileSystemSelector::setPath(const QString &path)
{
    QFileInfo info{path};
    auto old = m_data->m_fsModel->rootPath();
    if (info.exists() && info.isDir()) {
        m_data->m_fsModel->setRootPath(path);
        m_data->m_fsView->setRootIndex(m_data->m_fsModel->index(path));
        appContext()->configManager()->set(CONFIG_PATH, path);
    } else {
        QZ_ERROR("Qz:Explorer") << "Invalid directory path "
                                << path << " given";
        m_data->m_pathEdit->setText(old);
    }
}

}
