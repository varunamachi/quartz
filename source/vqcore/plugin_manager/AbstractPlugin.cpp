

#include "AbstractPlugin.h"

namespace Vam
{

class AbstractPlugin::Impl
{
public:
    inline Impl( const QString &pluginId,
                 const QString &pluginType,
                 const QString &pluginName,
                 const QString &pluginDesc )
        : m_pluginId( pluginId )
        , m_pluginType( pluginType )
        , m_pluginName( pluginName )
        , m_pluginDesc( pluginDesc )
    {

    }

    inline const QString & pluginId() const
    {
        return m_pluginId;
    }

    inline const QString & pluginType() const
    {
        return m_pluginType;
    }

    inline const QString & pluginName() const
    {
        return m_pluginName;
    }

    inline const QString & pluginDescription() const
    {
        return m_pluginDesc;
    }

private:
    QString m_pluginId;

    QString m_pluginType;

    QString m_pluginName;

    QString m_pluginDesc;
};


AbstractPlugin::~AbstractPlugin()
{

}

const QString & AbstractPlugin::pluginId() const
{
    return m_impl->pluginId();
}


const QString & AbstractPlugin::pluginType() const
{
    return m_impl->pluginType();
}


const QString & AbstractPlugin::pluginName() const
{
    return m_impl->pluginName();
}


const QString & AbstractPlugin::pluginDescription() const
{
    return m_impl->pluginDescription();
}


}
