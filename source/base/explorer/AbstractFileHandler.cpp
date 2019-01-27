#include <QStringList>

#include "AbstractFileHandler.h"

namespace Quartz {

struct AbstractFileHandler::Data
{
    explicit Data(const QStringList &extns)
        : m_extensions(extns)
    {

    }

    QStringList m_extensions;
};

AbstractFileHandler::AbstractFileHandler(const QStringList &extensions)
    : m_data(std::make_unique<Data>(extensions))
{

}

AbstractFileHandler::~AbstractFileHandler()
{

}

const QStringList &AbstractFileHandler::supportedExtensions() const
{
    return m_data->m_extensions;
}

}
