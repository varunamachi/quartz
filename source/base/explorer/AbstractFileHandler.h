#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

class QStringList;
class QFile;

namespace Quartz {

enum class FileHandlerType {
    Editor,
    Viewer,
    Transformer,
};


class QUARTZ_BASE_API AbstractFileHandler
{
public:
    AbstractFileHandler(
            const QString &name,
            FileHandlerType type,
            const QStringList &extensions);

    virtual ~AbstractFileHandler();

    const QStringList & supportedExtensions() const;

    const QString & name() const;

    FileHandlerType type() const;

    virtual bool handle(const QFile &file) = 0;



private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
