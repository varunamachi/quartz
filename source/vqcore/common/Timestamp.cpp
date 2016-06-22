#include <memory>
#include <chrono>

#include "../platform/Platform.h"

#ifdef VQ_WINDOWS
    #include <Winbase.h>
#endif

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

    void setVal( Timestamp::TimeVal timeVal )
    {
        m_val = timeVal;
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
    auto one = static_cast< TimeVal >( 0x01b21dd2 );
    auto epochVal = m_data->val() + (( one << 32 ) - 0x13814000 );
    return epochVal * 10;
}


Timestamp::TimeVal Timestamp::toPosixMicroSec() const
{
    return m_data->val();
}


Timestamp Timestamp::now()
{
    using namespace std::chrono;
    auto now = system_clock::now().time_since_epoch();
    auto micros = duration_cast< microseconds >( now ).count();
    return Timestamp { micros };
}


Timestamp Timestamp::fromPosixEpoch( const std::time_t &time )
{
    return Timestamp{ static_cast< TimeVal >( time ) * 1000000 } ;
}


Timestamp Timestamp::fromUTCTime( const TimeVal &utc )
{
    auto one = static_cast< TimeVal >( 0x01b21dd2 );
    auto epochVal = utc - (( one << 32 ) + 0x13814000 );
    return Timestamp{ epochVal / 10 };
}

}
