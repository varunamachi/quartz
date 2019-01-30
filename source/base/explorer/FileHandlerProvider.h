#pragma once

#include <functional>
#include <memory>

#include <QVector>

#include <core/ext/Extension.h>

#include "../QuartzBase.h"

class QWidget;
class QIcon;

namespace Quartz {

class AbstractFileHandler;
class FileHandlerInfo;

class QUARTZ_BASE_API FileHandlerProvider : public Ext::Extension
{
public:
    FileHandlerProvider(const QString &extID,
                        const QString &extName);

    ~FileHandlerProvider() override;

    virtual QVector<std::shared_ptr<FileHandlerInfo>> handlerInfos() = 0;

    static const QString EXTENSION_TYPE;

};

}
