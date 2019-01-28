#pragma once

#include <core/ext/Extension.h>

namespace Quartz {

class AbstractFileHandler;

class AbstractFileHandlerProvider : public Ext::Extension
{
public:
    AbstractFileHandlerProvider(const QString &extID, const QString &extName);

    ~AbstractFileHandlerProvider();

    virtual std::shared_ptr<AbstractFileHandler> createHandler() = 0;

    static const QString EXTENSION_TYPE;
};

}
