#include <QVBoxLayout>
#include <QHash>
#include <QVector>
#include <QFileInfo>

#include "AbstractFileHandler.h"
#include "FileHandlerManager.h"
#include "AbstractFileHandlerProvider.h"

namespace Quartz {

struct FileHandlerManager::Data
{
    explicit Data(QWidget *parent) { }

    QVector<std::shared_ptr<AbstractFileHandler>> m_handlers;

    QMultiHash<QString, AbstractFileHandler *> m_handlerMapping;

    QHash<QString, AbstractFileHandler *> m_defaultHandlers;
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
    this->setLayout(layout);
}

FileHandlerManager::~FileHandlerManager()
{

}

void FileHandlerManager::registerFileHandler(
        std::shared_ptr<AbstractFileHandler> handler)
{
    m_data->m_handlers.append(handler);
    for (auto ext : handler->supportedExtensions()) {
        m_data->m_handlerMapping.insert(ext, handler.get());
        if (!m_data->m_defaultHandlers.contains(ext)) {
            m_data->m_defaultHandlers[ext] = handler.get();
        }
    }
}

void FileHandlerManager::handle(const QString &path)
{
    QFileInfo info{path};
//    auto handler = m_data->m_defaultHandlers[info.d]
    //    auto handler = m_data->m_defaultHandlers[]
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
    return true;
}

bool FileHandlerManager::finalizeExtension()
{
    return true;
}

}
