#pragma once

#include <core/ext/Extension.h>

namespace Quartz {

class AbstractFileHandler;

class FileHandlerProvider : public Ext::Extension
{
public:
    FileHandlerProvider();

    virtual std::shared_ptr<AbstractFileHandler> createHandler() = 0;
};

}
