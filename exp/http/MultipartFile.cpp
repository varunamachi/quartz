
#include "MultipartFile.h"

namespace Quartz { namespace Http {

struct MultipartFile::Data
{
    Data( const QString &fileName,
          const QString &contentType,
          std::size_t offset,
          std::size_t length )
        : m_fileName{ fileName }
        , m_contentType{ contentType }
        , m_offset{ offset }
        , m_length{ length }
    {

    }

    Data( const Data &other )
    {
        //@todo implement
    }

    QString m_fileName;

    QString m_contentType;

    std::size_t m_offset;

    std::size_t m_length;
};


MultipartFile::~MultipartFile()
{

}

const QString & MultipartFile::fileName() const
{
    return m_data->m_fileName;
}

const QString & MultipartFile::contentType() const
{
    return m_data->m_contentType;
}

std::size_t MultipartFile::offset() const
{
   return m_data->m_offset;
}

std::size_t MultipartFile::length() const
{
    return m_data->m_length;
}

} }
