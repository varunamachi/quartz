#include <memory>

#include "Timestamp.h"

namespace Vq {

class Timestamp::Data
{

public:
    explicit Data( const Timestamp::TimeVal &val )
        : m_val( val )
    {

    }

    Timestamp::TimeVal & val()
    {
        return m_val;
    }


private:
    Timestamp::TimeVal m_val;
};


Timestamp::Timestamp( const TimeVal &timeVal )
    : m_data( std::make_unique< Timestamp::Data >( timeVal ))
{

}



Timestamp::Timestamp( const Timestamp &other )
    : m_data( std::make_unique< Timestamp::Data >( other.m_data->val() ))
{
}



Timestamp::Timestamp( Timestamp &&other )
    : m_data( std::make_unique< Timestamp::Data >(
                  std::move( other.m_data->val() )))
{
}


Timestamp & Timestamp::operator = ( const Timestamp &other )
{
    *m_data = *other.m_data;
    return *this;
}


Timestamp & Timestamp::operator = ( const Timestamp &&other )
{
    *m_data = std::move( *other.m_data );
    return *this;
}


bool Timestamp::operator == ( const Timestamp &other )
{
    return m_data->val() == other.m_data->val();
}


bool Timestamp::operator != ( const Timestamp &other )
{
    return ! ( *this == other );
}


bool Timestamp::operator >  ( const Timestamp &other )
{
    return m_data->val() > other.m_data->val();
}


bool Timestamp::operator >= ( const Timestamp &other )
{
    return m_data->val() >= other.m_data->val();
}


bool Timestamp::operator <  ( const Timestamp &other )
{
    return m_data->val() < other.m_data->val();
}


bool Timestamp::operator <= ( const Timestamp &other )
{
    return m_data->val() <= other.m_data->val();
}


Timestamp Timestamp::operator + ( const Timestamp &other )
{
    auto sum = m_data->val() + other.m_data->val();
    return Timestamp{ sum };
}


Timestamp Timestamp::operator - ( const Timestamp &other )
{
    auto diff = m_data->val() - other.m_data->val();
    return Timestamp{ diff};
}


Timestamp & Timestamp::operator += ( const Timestamp &other )
{
    m_data->val() += other.m_data->val();
    return *this;
}


Timestamp & Timestamp::operator -= ( const Timestamp &other )
{
    m_data->val() -= other.m_data->val();
    return *this;

}


Timestamp::TimeVal Timestamp::toUTCMicroSec() const
{

}


Timestamp::TimeVal Timestamp::toPosixMicroSec() const
{

}


Timestamp Timestamp::now()
{

}


Timestamp Timestamp::fromPosixEpoch( const std::time_t &time )
{

}


Timestamp Timestamp::fromUTCTime( const TimeVal &utc )
{

}

}
