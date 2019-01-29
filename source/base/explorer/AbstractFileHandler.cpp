#include <QStringList>

#include "AbstractFileHandler.h"

namespace Quartz {

struct AbstractFileHandler::Data
{
    explicit Data(const QString &name,
                  const FileHandlerType type)
        : m_name(name)
        , m_type(type)
    {

    }

    QString m_name;

    FileHandlerType m_type;
};

AbstractFileHandler::AbstractFileHandler(const QString &name,
                                         FileHandlerType type,
                                         QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(name, type))
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

}
