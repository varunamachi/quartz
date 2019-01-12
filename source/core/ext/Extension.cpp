
#include "Extension.h"

namespace Quartz { namespace Ext {

struct Extension::Data
{
    Data(const QString &extensionId,
          const QString &extensionName,
          const QString &extensionType)
        : m_extensionId(extensionId)
        , m_extensionName(extensionName)
        , m_extensionType(extensionType)
    {

    }

    const QString &m_extensionId;

    const QString &m_extensionName;

    const QString &m_extensionType;

};


Extension::Extension(const QString &extensionId,
                                const QString &extensionName,
                                const QString &extensionType)
    : m_data(std::make_unique<Data>(extensionId, extensionName, extensionType))
{

}

Extension::~Extension()
{

}

const QString &Extension::extensionId() const
{
    return m_data->m_extensionId;
}

const QString &Extension::extensionName() const
{
    return m_data->m_extensionName;
}

const QString &Extension::extensionType() const
{
    return m_data->m_extensionType;
}

} }
