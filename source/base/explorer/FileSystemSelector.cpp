#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QLineEdit>
#include <QPushButton>
#include <QFileInfo>
#include <QFileDialog>
#include <QMenu>
#include <QApplication>
#include <QClipboard>

#include <core/logger/Logging.h>
#include <core/utils/History.h>
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

enum class HistoryDirection
{
    Backward,
    Forward,
    None
};

struct FileSystemSelector::Data
{
    explicit Data(QWidget *parent)
        : m_fsModel(new QFileSystemModel(parent))
        , m_fsView(new QTreeView(parent))
        , m_pathEdit(new QLineEdit(parent))
        , m_browseBtn(new QPushButton(getIcon(FAIcon::FolderOpen), "", parent))
        , m_backBtn(new QPushButton(getIcon(MatIcon::ArrowBack), "", parent))
        , m_upBtn(new QPushButton(getIcon(MatIcon::ArrowUpward), "", parent))
        , m_fwdBtn(new QPushButton(getIcon(MatIcon::ArrowForward), "", parent))
        , m_menu(new QMenu(parent))
    {
        m_fsView->setModel(m_fsModel);
        for (int i = 1; i < m_fsModel->columnCount(); ++i) {
            m_fsView->hideColumn(i);
        }
    }


    QFileSystemModel *m_fsModel;

    QTreeView *m_fsView;

    QLineEdit *m_pathEdit;

    QPushButton *m_browseBtn;

    QPushButton *m_backBtn;

    QPushButton *m_upBtn;

    QPushButton *m_fwdBtn;

    QMenu *m_menu;

    QString m_contextPath = QStringLiteral("");

    History m_history;

};

FileSystemSelector::FileSystemSelector(QWidget *parent)
    : AbstractSelector(
          SELECTOR_ID,
          SELECTOR_NAME,
          getNormalIcon(FAIcon::Eye),
          getActiveIcon(FAIcon::Eye),
          parent)
    , m_data(std::make_unique<Data>(this))
{

    auto topLayout = new QHBoxLayout();
    topLayout->addWidget(m_data->m_backBtn);
    topLayout->addWidget(m_data->m_upBtn);
    topLayout->addWidget(m_data->m_fwdBtn);
    topLayout->addStretch();
    topLayout->addWidget(m_data->m_browseBtn);
    topLayout->setContentsMargins({5, 0, 0, 0});

    auto lyt = new QVBoxLayout();
    lyt->addWidget(m_data->m_pathEdit);
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

    auto copyPath = new QAction(getIcon(FAIcon::Copy), tr("Copy Path"), this);
    auto explore = new QAction(getIcon(FAIcon::Eye), tr("Explore Here"), this);
    m_data->m_menu->addAction(copyPath);
    m_data->m_menu->addAction(explore);
    m_data->m_fsView->setContextMenuPolicy(Qt::CustomContextMenu);

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
    connect(m_data->m_browseBtn,
            &QPushButton::released,
            [=]() {
        auto dirPath = QFileDialog::getExistingDirectory(
                    this,
                    tr("Explore directory"),
                    m_data->m_pathEdit->text());
        if (! dirPath.isEmpty()) {
            m_data->m_pathEdit->setText(dirPath);
            auto old = this->setPath(dirPath);
            if (!old.isEmpty()) {
                m_data->m_history.add(old);
            }
        }
    });
    connect(m_data->m_pathEdit,
            &QLineEdit::editingFinished,
            [=](){
        auto old = this->setPath(m_data->m_pathEdit->text());
        if (!old.isEmpty()) {
            m_data->m_history.add(old);
        }
    });
    connect(m_data->m_fsView,
            &QWidget::customContextMenuRequested,
            [this](const QPoint &pos) {
        auto gpos = this->mapToGlobal(pos);
        auto index = m_data->m_fsView->indexAt(pos);
        m_data->m_contextPath = m_data->m_fsModel->filePath(index);
        m_data->m_menu->exec(gpos);
    });
    connect(copyPath,
            &QAction::triggered,
            [this]() {
        if (!m_data->m_contextPath.isEmpty()) {
            auto clipboard = QApplication::clipboard();
            clipboard->setText(m_data->m_contextPath);
            m_data->m_contextPath = QStringLiteral("");
        }
    });
    connect(explore,
            &QAction::triggered,
            [this]() {
        if (!m_data->m_contextPath.isEmpty()) {
            m_data->m_pathEdit->setText(m_data->m_contextPath);
            const auto old = this->setPath(m_data->m_contextPath);
            if (!old.isEmpty()) {
                m_data->m_history.add(old);
            }
            m_data->m_contextPath = QStringLiteral("");
        }
    });
    connect(m_data->m_upBtn,
            &QPushButton::released,
            [this]() {
        QFileInfo info{m_data->m_fsModel->rootPath()};
        auto path = info.dir().path();
        if (!path.isEmpty()) {
            m_data->m_pathEdit->setText(path);
            const auto old = this->setPath(path);
            if (!old.isEmpty()) {
                m_data->m_history.add(old);
            }
        }
    });
    connect(m_data->m_backBtn,
            &QPushButton::released,
            [this]() {
        const auto &path = m_data->m_history.prev();
        if (! path.isEmpty()) {
            this->setPath(path);
            m_data->m_pathEdit->setText(path);
        }
    });
    connect(m_data->m_fwdBtn,
            &QPushButton::released,
            [this]() {
        const auto &path = m_data->m_history.next();
        if (! path.isEmpty()) {
            this->setPath(path);
            m_data->m_pathEdit->setText(path);
        }
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

QString FileSystemSelector::setPath(const QString &path)
{
    QFileInfo info{path};
    auto old = m_data->m_fsModel->rootPath();
    if (info.exists() && info.isDir()) {
        m_data->m_fsModel->setRootPath(path);
        m_data->m_fsView->setRootIndex(m_data->m_fsModel->index(path));
        appContext()->configManager()->set(CONFIG_PATH, path);
        return old;
    }
    QZ_ERROR("Qz:Explorer") << "Invalid directory path "
                            << path << " given";
    m_data->m_pathEdit->setText(old);
    return QStringLiteral("");
}

}
