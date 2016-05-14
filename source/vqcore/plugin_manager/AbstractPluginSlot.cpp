
#include "AbstractPluginSlot.h"

namespace Vam {

class AbstractPluginSlot::Data
{
public:
    inline Data( const QString &slotId,
                 const QString &slotName,
                 const QString &slotDesc )
        : m_slotId( slotId )
        , m_slotName( slotName )
        , m_slotDesc( slotDesc )
    {

    }

    inline const QString & slotId() const
    {
        return  m_slotId;
    }

    inline const QString & slotName() const
    {
        return m_slotName;
    }

    inline const QString & slotDescription() const
    {
        return m_slotDesc;
    }

private:
    QString m_slotId;

    QString m_slotName;

    QString m_slotDesc;
};


const QString  &AbstractPluginSlot::slotId() const
{
    return m_data->slotId();
}


const QString & AbstractPluginSlot::slotName() const
{
    return m_data->slotName();
}


const QString & AbstractPluginSlot::slotDescription() const
{
    return m_data->slotDescription();
}


AbstractPluginSlot::~AbstractPluginSlot()
{
    //
}

}
