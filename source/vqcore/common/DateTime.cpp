
#include <memory>
#include <algorithm>

#include "DateTime.h"
#include "Timestamp.h"

namespace Vq {

class DateTime::Data
{
public:
    explicit Data( Timestamp::TimeVal val )
        : m_val( val )
    {

    }

    Data( Data &other )
        : m_val( other.m_val )
    {

    }

    Data( Data &&other )
        : m_val( std::move( other.m_val ))
    {

    }

    Data & operator = ( const Data &other )
    {
        this->m_val = other.m_val;
        return *this;
    }

    Data & operator = ( Data &&other )
    {
        this->m_val = std::move( other.m_val );
        other.m_val = 0;
        return *this;
    }

    Timestamp::TimeVal & val()
    {
        return m_val;
    }

    void setVal( Timestamp::TimeVal val )
    {
        m_val = val;
    }

private:
    Timestamp::TimeVal m_val;
};


DateTime::DateTime( const Timestamp &timestamp )
    : m_data( std::make_unique< DateTime::Data >( timestamp.value() ))
{

}


DateTime::DateTime( const DateTime &other )
    : m_data( std::make_unique< DateTime::Data >( other ))
{

}


DateTime::DateTime( DateTime &&other )
    : m_data( std::make_unique< DateTime::Data >( other ))
{

}


DateTime::~DateTime()
{

}


DateTime & DateTime::operator = ( const DateTime &other )
{
     ( *m_data ) = ( *other.m_data );
}


DateTime & DateTime::operator = ( const DateTime &&other )
{
     ( *m_data ) = std::move( *other.m_data );
}


int DateTime::year() const
{
    return 2000;
}


Month DateTime::month() const
{
    return Month::January;
}


WeekOfYearType DateTime::week( Day firstDayOfWeek ) const
{
    return WeekOfYearType( 1 );
}


Day DateTime::dayOfWeek() const
{
    return Day::Sunday;
}


DayOfMonthType DateTime::dayOfMonth() const
{
    return DayOfMonthType( 1 );
}


DayOfYearType DateTime::dayOfYear() const
{
    return DayOfYearType( 1 );
}


HourType DateTime::hour() const
{
    return HourType( 1 );
}


MinuteType DateTime::minute() const
{
    return MinuteType( 1 );
}


SecondType DateTime::second() const
{
    return SecondType( 1 );
}


MilliSecType DateTime::millisecond() const
{
    return MilliSecType( 1 );
}


MicroSecType DateTime::microsecond() const
{
    return MicroSecType( 1 );
}


Timestamp DateTime::timestamp() const
{
    return Timestamp( m_data->val() );
}


bool DateTime::operator == ( const DateTime &other ) const
{
    return m_data->val() == other.m_data->val();
}


bool DateTime::operator != ( const DateTime &other ) const
{
    ! ( *this == other );
}


bool DateTime::operator <  ( const DateTime &other ) const
{
    return m_data->val() < other.m_data->val();
}


bool DateTime::operator <= ( const DateTime &other ) const
{
    return m_data->val() <= other.m_data->val();
}


bool DateTime::operator >  ( const DateTime &other ) const
{
    return m_data->val() > other.m_data->val();
}


bool DateTime::operator >= ( const DateTime &other ) const
{
    return m_data->val() >= other.m_data->val();
}


DateTime DateTime::operator + ( const DateTime &other )
{
    auto val = m_data->val() + other.m_data->val();
    return DateTime( Timestamp( val ));
}


DateTime DateTime::operator - ( const DateTime &other )
{
    auto val = m_data->val() - other.m_data->val();
    return DateTime( Timestamp( val ));
}


DateTime & DateTime::operator += ( const DateTime &other )
{
    m_data->setVal( m_data->val() + other.m_data->val() );
    return *this;
}


DateTime & DateTime::operator -= ( const DateTime &other )
{
    m_data->setVal( m_data->val() - other.m_data->val() );
    return *this;
}


DateTime DateTime::now()
{
    DateTime now{ Timestamp::now() };
    return now;
}


}

