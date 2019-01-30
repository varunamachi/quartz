#include <QString>
#include <QStringList>
#include <QWidget>
#include <QIcon>


#include "FileHandlerInfo.h"

namespace Quartz {

struct FileHandlerInfo::Data
{
    Data(const QString &name,
         FileHandlerType type,
         const QStringList &extns,
         const QIcon &icon,
         FHCreator creatorFunc)
        : m_name(name)
        , m_type(type)
        , m_extensions(extns)
        , m_icon(icon)
        , m_creatorFunc(creatorFunc)
    {

    }

    QString m_name;

    FileHandlerType m_type;

    QStringList m_extensions;

    QIcon m_icon;

    FHCreator m_creatorFunc;
};

FileHandlerInfo::FileHandlerInfo(
        const QString &name,
        FileHandlerType type,
        const QStringList &extns,
        const QIcon &icon,
        FHCreator creatorFunc)
    : m_data(std::make_unique<Data>(name, type, extns, icon, creatorFunc))
{

}

FileHandlerInfo::FileHandlerInfo(FileHandlerInfo &&other)
    : m_data(std::move(other.m_data))
{

}

FileHandlerInfo::~FileHandlerInfo()
{

}

FileHandlerInfo & FileHandlerInfo::operator=(FileHandlerInfo &&other)
{
    this->m_data = std::move(other.m_data);
    return *this;
}

const QString & FileHandlerInfo::name() const
{
    return m_data->m_name;
}

FileHandlerType FileHandlerInfo::type() const
{
    return m_data->m_type;
}

const QStringList &FileHandlerInfo::extensions() const
{
    return m_data->m_extensions;
}

FHCreator FileHandlerInfo::creator() const
{
    return m_data->m_creatorFunc;
}

const QIcon &FileHandlerInfo::icon() const
{
    return m_data->m_icon;
}


}
