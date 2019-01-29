
#include "FileHandlerProvider.h"

namespace Quartz {

struct FileHandlerProvider::Data
{
    Data(const QStringList &extns, const FileHandlerCreator &creator)
        : m_creator(creator)
    {

    }

    FileHandlerCreator m_creator;
};

const QString FileHandlerProvider::EXTENSION_TYPE("qz.file_handler");

FileHandlerProvider::FileHandlerProvider(
        const QString &extID,
        const QString &extName,
        const FileHandlerCreator &creator)
    : Ext::Extension (extID, extName, EXTENSION_TYPE)
    , m_data(std::make_unique<Data>(creator))
{

}

FileHandlerProvider::~FileHandlerProvider()
{

}

const FileHandlerCreator & FileHandlerProvider::creator() const
{
    return m_data->m_creator;
}

}
