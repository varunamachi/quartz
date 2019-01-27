#pragma once

#include <memory>

#include "../QuartzBase.h"

class QStringList;
class QFile;

namespace Quartz {


class QUARTZ_BASE_API AbstractFileHandler
{
public:
    AbstractFileHandler(const QStringList &extensions);

    virtual ~AbstractFileHandler();

    const QStringList & supportedExtensions() const;

    virtual bool handle(const QFile &file) = 0;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
