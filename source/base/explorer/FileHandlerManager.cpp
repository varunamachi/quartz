#include <QVBoxLayout>
#include <QHash>
#include <QVector>
#include <QFileInfo>
#include <QTabWidget>

#include <core/logger/Logging.h>

#include "AbstractFileHandler.h"
#include "FileHandlerManager.h"
#include "FileHandlerProvider.h"

namespace Quartz {

struct FileHandlerManager::Data
{
    explicit Data(QWidget *parent)
        : m_stacker(new QTabWidget(parent))
    {

    }


    QTabWidget *m_stacker;

    QMultiHash<QString, FileHandlerCreator> m_handlerMapping;

    QHash<QString, FileHandlerCreator> m_defaultHandlers;

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
}

FileHandlerManager::~FileHandlerManager()
{

}

void FileHandlerManager::registerFileHandler(const FileHandlerCreator &creator)
{
    for (auto ext : creator.m_extensions) {
        m_data->m_handlerMapping.insert(ext, creator);
        if (!m_data->m_defaultHandlers.contains(ext)) {
            m_data->m_defaultHandlers[ext] = creator;
        }
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
        auto hndlr = creator.m_creatorFunc(m_data->m_stacker);
        m_data->m_cache[path] = hndlr;
        m_data->m_stacker->addTab(hndlr, creator.m_icon, info.fileName());
    } else {
        QZ_ERROR("Qz:Explorer") << "Could not find default handler for file "
                                << info.fileName();
        //show error message / toast??
    }
}

const QString &FileHandlerManager::extensionType() const
{
    return FileHandlerProvider::EXTENSION_TYPE;
}

const QString &FileHandlerManager::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool FileHandlerManager::handleExtension(Ext::Extension */*extension*/)
{
    return true;
}

bool FileHandlerManager::finalizeExtension()
{
    return true;
}

}
