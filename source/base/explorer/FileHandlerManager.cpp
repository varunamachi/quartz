#include <QVBoxLayout>
#include <QHash>
#include <QVector>
#include <QFileInfo>
#include <QTabWidget>

#include <core/logger/Logging.h>

#include "AbstractFileHandler.h"
#include "FileHandlerManager.h"
#include "AbstractFileHandlerProvider.h"
#include "FileHandlerInfo.h"

namespace Quartz {

struct FileHandlerManager::Data
{
    explicit Data(QWidget *parent)
        : m_stacker(new QTabWidget(parent))
    {
        m_stacker->setTabsClosable(true);
    }

    QTabWidget *m_stacker;

    QMultiHash<QString, std::shared_ptr<FileHandlerInfo>> m_handlerMapping;

    QHash<QString, FileHandlerInfo *> m_defaultHandlers;

    QHash<QString, AbstractFileHandler *> m_cache;

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
    layout->addWidget(m_data->m_stacker);
    this->setLayout(layout);

    connect(m_data->m_stacker,
            &QTabWidget::tabCloseRequested,
            [this](int index) {
        auto handler = qobject_cast<AbstractFileHandler *>(
                    m_data->m_stacker->widget(index));
        if (handler->close()) {
            m_data->m_stacker->removeTab(index);
        }
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
    //see if it is already opened, if so set it as current widget
    if (hndlr != nullptr) {
        m_data->m_stacker->setCurrentWidget(hndlr);
        return;
    }

    QFileInfo info{path};
    if (m_data->m_defaultHandlers.contains(info.suffix())) {
        auto &creator = m_data->m_defaultHandlers[info.suffix()];
        auto hndlr = creator->creator()(m_data->m_stacker);
        m_data->m_cache[path] = hndlr;
        if (hndlr != nullptr && hndlr->handle(path)) {
//            auto name = info.fileName().
            auto name = QFontMetrics(
                        m_data->m_stacker->font()).elidedText(
                        info.fileName(),
                        Qt::ElideMiddle,
                        80);
            auto index = m_data->m_stacker->addTab(hndlr,
                                                   creator->icon(),
                                                   name);
            m_data->m_stacker->setCurrentIndex(index);
        } else {
            QZ_ERROR("Qz:Explorer")
                    << "Handler " << creator->name() << " failed to handle - "
                    << path;
        }
    } else if(info.isFile()){
        QZ_ERROR("Qz:Explorer") << "Could not find default handler for file "
                                << info.fileName();
        //show error message / toast??
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

}
