#include <QStringList>

#include "AbstractFileHandler.h"

namespace Quartz {

struct AbstractFileHandler::Data
{
    explicit Data(const QString &name,
                  const FileHandlerType type,
                  const QStringList &extns)
        : m_name(name)
        , m_type(type)
        , m_extensions(extns)
    {

    }

    QString m_name;

    FileHandlerType m_type;

    QStringList m_extensions;
};

AbstractFileHandler::AbstractFileHandler(const QString &name,
                                         FileHandlerType type,
                                         const QStringList &extensions)
    : m_data(std::make_unique<Data>(name, type, extensions))
{

}

AbstractFileHandler::~AbstractFileHandler()
{

}

const QString &AbstractFileHandler::name() const
{
    return m_data->m_name;
}

FileHandlerType AbstractFileHandler::type() const
{
    return m_data->m_type;
}

const QStringList &AbstractFileHandler::supportedExtensions() const
{
    return m_data->m_extensions;
}

}
