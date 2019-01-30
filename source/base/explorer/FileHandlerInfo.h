#pragma once

#include <memory>
#include <functional>

#include "../QuartzBase.h"

class QString;
class QStringList;
class QIcon;
class QWidget;

namespace Quartz {

class AbstractFileHandler;
using FHCreator = std::function<AbstractFileHandler *(QWidget *parent)>;

enum class FileHandlerType {
    Editor,
    Viewer,
    Transformer,
};


class QUARTZ_BASE_API FileHandlerInfo
{
public:
    FileHandlerInfo(const QString &name,
                    FileHandlerType type,
                    const QStringList &extns,
                    const QIcon &icon,
                    FHCreator creatorFunc);

    FileHandlerInfo(FileHandlerInfo &&other);

    ~FileHandlerInfo();

    FileHandlerInfo &  operator= (FileHandlerInfo &&other);

    FileHandlerInfo(const FileHandlerInfo &other) = delete;

    FileHandlerInfo & operator= (const FileHandlerInfo &other) = delete;

    const QString & name() const;

    FileHandlerType type() const;

    const QStringList & extensions() const;

    const QIcon & icon() const;

    FHCreator creator() const;


private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
