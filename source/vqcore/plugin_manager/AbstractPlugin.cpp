

#include "AbstractPlugin.h"

namespace Vq
{

class AbstractPlugin::Impl
{
public:
    inline Impl( const std::string &pluginId,
                 const std::string &pluginType,
                 const std::string &pluginName,
                 const std::string &pluginDesc )
        : m_pluginId( pluginId )
        , m_pluginType( pluginType )
        , m_pluginName( pluginName )
        , m_pluginDesc( pluginDesc )
    {

    }

    inline const std::string & pluginId() const
    {
        return m_pluginId;
    }

    inline const std::string & pluginType() const
    {
        return m_pluginType;
    }

    inline const std::string & pluginName() const
    {
        return m_pluginName;
    }

    inline const std::string & pluginDescription() const
    {
        return m_pluginDesc;
    }

private:
    std::string m_pluginId;

    std::string m_pluginType;

    std::string m_pluginName;

    std::string m_pluginDesc;
};


AbstractPlugin::~AbstractPlugin()
{

}

const std::string & AbstractPlugin::pluginId() const
{
    return m_impl->pluginId();
}


const std::string & AbstractPlugin::pluginType() const
{
    return m_impl->pluginType();
}


const std::string & AbstractPlugin::pluginName() const
{
    return m_impl->pluginName();
}


const std::string & AbstractPlugin::pluginDescription() const
{
    return m_impl->pluginDescription();
}


}
