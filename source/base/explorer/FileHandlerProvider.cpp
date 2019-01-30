
#include "FileHandlerInfo.h"
#include "FileHandlerProvider.h"

namespace Quartz {

const QString FileHandlerProvider::EXTENSION_TYPE("qz.file_handler");

FileHandlerProvider::FileHandlerProvider(
        const QString &extID,
        const QString &extName)
    : Ext::Extension (extID, extName, EXTENSION_TYPE)
{

}

FileHandlerProvider::~FileHandlerProvider()
{

}

}
