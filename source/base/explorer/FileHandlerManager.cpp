#include <QVBoxLayout>
#include <QHash>
#include <QVector>
#include <QFileInfo>

#include "AbstractFileHandler.h"
#include "FileHandlerManager.h"

namespace Quartz {

struct FileHandlerManager::Data
{
    explicit Data(QWidget *parent) { }

    QVector<std::shared_ptr<AbstractFileHandler>> m_handlers;

    QMultiHash<QString, AbstractFileHandler *> m_handlerMapping;

    QHash<QString, AbstractFileHandler *> m_defaultHandlers;
};

const QString FileHandlerManager::CONTENT_ID("qz.editor_manager");
const QString FileHandlerManager::CONTENT_NAME("Editor");
const QString FileHandlerManager::CONTENT_KIND("editor");

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

void FileHandlerManager::addHandler(
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
//    auto handler = m_data->m_defaultHandlers[info.]
//    auto handler = m_data->m_defaultHandlers[]
}

}
