
#include "FileHandlerInfo.h"
#include "AbstractFileHandlerProvider.h"

namespace Quartz {

const QString AbstractFileHandlerProvider::EXTENSION_TYPE("qz.file_handler");

AbstractFileHandlerProvider::AbstractFileHandlerProvider(
        const QString &extID,
        const QString &extName)
    : Ext::Extension (extID, extName, EXTENSION_TYPE)
{

}

AbstractFileHandlerProvider::~AbstractFileHandlerProvider()
{

}

}
