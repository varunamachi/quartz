
#include "AbstractPluginSlot.h"

namespace Vq {

class AbstractPluginSlot::Data
{
public:
    inline Data( const std::string &slotId,
                 const std::string &slotName,
                 const std::string &slotDesc )
        : m_slotId( slotId )
        , m_slotName( slotName )
        , m_slotDesc( slotDesc )
    {

    }

    inline const std::string & slotId() const
    {
        return  m_slotId;
    }

    inline const std::string & slotName() const
    {
        return m_slotName;
    }

    inline const std::string & slotDescription() const
    {
        return m_slotDesc;
    }

private:
    std::string m_slotId;

    std::string m_slotName;

    std::string m_slotDesc;
};


const std::string  &AbstractPluginSlot::slotId() const
{
    return m_data->slotId();
}


const std::string & AbstractPluginSlot::slotName() const
{
    return m_data->slotName();
}


const std::string & AbstractPluginSlot::slotDescription() const
{
    return m_data->slotDescription();
}


AbstractPluginSlot::~AbstractPluginSlot()
{
    //
}

}
