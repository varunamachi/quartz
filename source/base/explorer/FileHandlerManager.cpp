#include <QVBoxLayout>
#include <QHash>
#include <QVector>
#include <QFileInfo>
#include <QTabWidget>
#include <QTextStream>
#include <QTabBar>
#include <QMouseEvent>
#include <QObject>
#include <QDebug>
#include <QMenu>
#include <QTabBar>
#include <QStackedWidget>
#include <QToolButton>

#include <core/logger/Logging.h>
#include <core/app_config/ConfigManager.h>

#include <common/iconstore/IconFontStore.h>

#include "../QzAppContext.h"
#include "AbstractFileHandler.h"
#include "FileHandlerManager.h"
#include "AbstractFileHandlerProvider.h"
#include "FileHandlerInfo.h"

namespace Quartz {

struct FileHandlerManager::Data
{
    explicit Data(QWidget *parent)
        : m_tabber(new QTabWidget(parent))
        , m_tabMenu(new QMenu())
        , m_menuButton(new QToolButton(parent))
    {
        m_tabber->setTabsClosable(true);
        m_menuButton->setIcon(getIcon(MatIcon::Menu));
        m_tabber->setCornerWidget(m_menuButton);
        m_menuButton->setMenu(m_tabMenu);
        m_menuButton->setPopupMode(QToolButton::InstantPopup);
    }

    QTabWidget *m_tabber;

    QMenu *m_tabMenu;

    QToolButton *m_menuButton;

    QMultiHash<QString, std::shared_ptr<FileHandlerInfo>> m_handlerMapping;

    QHash<QString, FileHandlerInfo *> m_defaultHandlers;

    QHash<QString, AbstractFileHandler *> m_cache;

    std::shared_ptr<FileHandlerInfo> m_dirHandler;

    int m_index = -1;

};

const QString FileHandlerManager::CONTENT_ID("qz.file_contet_manager");
const QString FileHandlerManager::CONTENT_NAME("Files");
const QString FileHandlerManager::CONTENT_KIND("viewer_editor");
const QString FileHandlerManager::ADAPTER_NAME("File View/Editor Manager");

FileHandlerManager::FileHandlerManager(QWidget *parent)
    : ContentWidget(CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent)
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QVBoxLayout();
    layout->addWidget(m_data->m_tabber);
    this->setLayout(layout);

    m_data->m_tabber->tabBar()->installEventFilter(this);

    auto closeAllAction = new QAction(tr("Close All"), this);
    auto closeRightAction = new QAction(tr("Close All - Right"), this);
    auto closeLeftAction = new QAction(tr("Close All - Left"), this);
    m_data->m_tabMenu->addAction(closeAllAction);
    m_data->m_tabMenu->addAction(closeLeftAction);
    m_data->m_tabMenu->addAction(closeRightAction);

    connect(m_data->m_tabber,
            &QTabWidget::tabCloseRequested,
            this,
            &FileHandlerManager::remove);
    connect(closeAllAction,
            &QAction::triggered,
            [this]() {
       m_data->m_tabber->clear();
       for (auto hnd : m_data->m_cache) {
           hnd->close();
           hnd->deleteLater();
       }
       m_data->m_cache.clear();
    });
    connect(closeLeftAction,
            &QAction::triggered,
            [this]() {
        if (m_data->m_index == -1) {
            m_data->m_index = m_data->m_tabber->currentIndex();
        }
        auto count = m_data->m_tabber->count();
        if (m_data->m_index > 0 && m_data->m_index < count)  {
            for (auto i = 0; i < m_data->m_index; ++i) {
                remove(0);
            }
        }
        m_data->m_index = -1;
    });
    connect(closeRightAction,
            &QAction::triggered,
            [this]() {
        if (m_data->m_index == -1) {
            m_data->m_index = m_data->m_tabber->currentIndex();
        }
        if (m_data->m_index >= 0
                && m_data->m_index < m_data->m_tabber->count()) {
            while (m_data->m_tabber->count() != (m_data->m_index + 1)) {
                remove(m_data->m_tabber->count() - 1);
            }
        }
        m_data->m_index = -1;
    });
}

FileHandlerManager::~FileHandlerManager()
{

}

void FileHandlerManager::registerFileHandler(
        std::shared_ptr<FileHandlerInfo> fhinfo)
{
    for (auto ext : fhinfo->extensions()) {
        if (!m_data->m_defaultHandlers.contains(ext)) {
            m_data->m_defaultHandlers[ext] = fhinfo.get();
        }
        m_data->m_handlerMapping.insert(ext, std::move(fhinfo));
    }
}

void FileHandlerManager::handle(const QString &path)
{
    auto hndlr = m_data->m_cache[path];
    QIcon icon;
    if (hndlr != nullptr) {
        m_data->m_tabber->setCurrentWidget(hndlr);
        return;
    }

    QFileInfo info{path};
    if (info.isDir() && m_data->m_dirHandler != nullptr) {
        //handle
    } else if (m_data->m_defaultHandlers.contains(info.suffix())) {
        auto &creator = m_data->m_defaultHandlers[info.suffix()];
        hndlr = creator->creator()(m_data->m_tabber);
        icon = creator->icon();
    } else if(info.isFile()){
        QZ_WARN("Qz:Explorer") << "Could not find default handler for file "
                                << info.fileName();
        auto &creator = m_data->m_defaultHandlers[""];
        hndlr = creator->creator()(m_data->m_tabber);
        icon = creator->icon();
    }

    m_data->m_cache[path] = hndlr;
    if (hndlr != nullptr && hndlr->handle(path)) {
        auto name = QFontMetrics(m_data->m_tabber->font()).elidedText(
                    info.fileName(),
                    Qt::ElideMiddle,
                    80);
        auto index = m_data->m_tabber->addTab(hndlr, icon, name);
        m_data->m_tabber->setTabToolTip(index, path);
        m_data->m_tabber->setCurrentIndex(index);
        connect(hndlr,
                &AbstractFileHandler::dirtyStateChanged,
                [this, name, index](bool value) {
            auto nm = name;
            if (value) {
                nm = name + "*";
            }
            m_data->m_tabber->setTabText(index, nm);
        });
    } else {
        QZ_ERROR("Qz:Explorer") << "Failed to handle file at " << path;
    }

}

const QString &FileHandlerManager::extensionType() const
{
    return AbstractFileHandlerProvider::EXTENSION_TYPE;
}

const QString &FileHandlerManager::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool FileHandlerManager::handleExtension(Ext::Extension *extension)
{
    auto handlerProvider = dynamic_cast<AbstractFileHandlerProvider *>(
                extension);
    if (handlerProvider != nullptr) {
        for(auto & info : handlerProvider->handlerInfos()) {
            registerFileHandler(info);
        }
    } else {
        QZ_ERROR("Qz:Explorer")
                << "Invalid actionbar extension provided: "
                << (extension != nullptr ? extension->extensionId() : "<null>");
    }
    return false;
}

bool FileHandlerManager::finalizeExtension()
{
    return true;
}

void FileHandlerManager::remove(int index)
{
    auto handler = qobject_cast<AbstractFileHandler *>(
                m_data->m_tabber->widget(index));
    if (handler->close()) {
        auto widget = m_data->m_cache.value(handler->path());
        m_data->m_cache.remove(handler->path());
        m_data->m_tabber->removeTab(index);
        widget->deleteLater();
    }
}

bool FileHandlerManager::eventFilter(QObject *obj, QEvent *event)
{
    auto res = false;
    auto tabBar = qobject_cast<QTabBar *>(obj);
    if (event->type() == QEvent::MouseButtonRelease && tabBar != nullptr) {
        auto mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            m_data->m_index = tabBar->tabAt(mouseEvent->pos());
            m_data->m_tabMenu->exec(mouseEvent->globalPos());
            res = true;
        }
    } else {
        return QObject::eventFilter(obj, event);
    }
    return res;
}

}
