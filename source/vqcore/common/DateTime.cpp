
#include <memory>
#include <algorithm>

#include "DateTime.h"
#include "Timestamp.h"

//Implementation is based on Poco::DateTime

namespace Vq {

const Day DAYS[ 7 ] = {
    Day::Monday,
    Day::Tuesday,
    Day::Wednesday,
    Day::Thursday,
    Day::Friday,
    Day::Saturday,
    Day::Sunday
};

const Month MONTHS[ 12 ] = {
    Month::January,
    Month::February,
    Month::March,
    Month::April,
    Month::May,
    Month::June,
    Month::July,
    Month::August,
    Month::September,
    Month::October,
    Month::November,
    Month::December
};


const int DAYS_IN_MONTH[ 13 ] = {
    -1,
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
};


static inline double toJulianDay( Timestamp::TimeVal utcTime ) noexcept
{
    auto utcDays = static_cast< double >( utcTime ) / 864000000000.0;
    utcDays = utcDays + 2299160.5;
    return utcDays;
}


static inline Timestamp::TimeVal fromJulianDay( double julianDay ) noexcept
{
    auto utcTime = ( julianDay - 2299160.5 ) * 864000000000.0;
    return Timestamp::TimeVal( utcTime );
}

static inline bool isLeapYear( int year ) noexcept
{
    bool result = (( year % 4 == 0 )
                   && ( year % 100 != 0 ))
            || year % 400 == 0;
    return result;
}


static inline int daysInMonth( int year, int month ) noexcept
{
    month = std::min( 12, month );
    int numDays = DAYS_IN_MONTH[ month ];
    if( month == 2 && isLeapYear( year )) {
        numDays = 29;
    }
    return numDays;
}



class DateTime::Data
{
public:
    inline explicit Data( Timestamp::TimeVal val )
        : m_utcVal( val )
        , m_year( 0 )
        , m_month( Month::January )
        , m_day( DayOfMonthType( 1 ))
        , m_hour( HourType( 0 ))
        , m_minute( MinuteType( 0 ))
        , m_second( SecondType( 0 ))
        , m_msec( MilliSecType( 0 ))
        , m_usec( MicroSecType( 0 ))
        , m_julianDay( toJulianDay( val ))

    {

    }

    inline Data( Data &other )
        : m_utcVal( other.m_utcVal )
        , m_year( other.m_year )
        , m_month( other.m_month )
        , m_day( other.m_day )
        , m_hour( other.m_hour )
        , m_minute( other.m_minute )
        , m_second( other.m_second )
        , m_msec( other.m_msec )
        , m_usec( other.m_usec )
        , m_julianDay( other.m_julianDay )
    {

    }

    inline Data( Data &&other )
        : m_utcVal( std::move( other.m_utcVal ))
        , m_year( std::move( other.m_year ))
        , m_month( std::move( other.m_month ))
        , m_day( std::move( other.m_day ))
        , m_hour( std::move( other.m_hour ))
        , m_minute( std::move( other.m_minute ))
        , m_second( std::move( other.m_second ))
        , m_msec( std::move( other.m_msec ))
        , m_usec( std::move( other.m_usec ))
        , m_julianDay( std::move( other.m_julianDay ))
    {

    }

    inline Data & operator = ( const Data &other )
    {
        this->m_utcVal = other.m_utcVal;
        return *this;
    }

    inline Data & operator = ( Data &&other )
    {
        this->m_utcVal = std::move( other.m_utcVal );
        other.m_utcVal = 0;
        return *this;
    }

    inline Timestamp::TimeVal & val()
    {
        return m_utcVal;
    }

    inline void setVal( Timestamp::TimeVal val )
    {
        m_utcVal = val;
    }

    inline int year()  const
    {
        return m_year;
    }

    inline Month month() const
    {
        return m_month;
    }

    inline const DayOfMonthType & dayOfMonth() const
    {
        return m_day;
    }

    inline const HourType & hour() const
    {
        return m_hour;
    }

    inline const MinuteType & minute() const
    {
        return m_minute;
    }

    inline const SecondType & second() const
    {
        return m_second;
    }

    inline const MilliSecType & millisecond() const
    {
        return m_msec;
    }

    inline const MicroSecType & microsecond() const
    {
        return m_usec;
    }

private:
    void compute();

    Timestamp::TimeVal m_utcVal;

    int m_year;

    Month m_month;

    DayOfMonthType m_day;

    HourType m_hour;

    MinuteType m_minute;

    SecondType m_second;

    MilliSecType m_msec;

    MicroSecType m_usec;

    double m_julianDay;


};


void DateTime::Data::compute()
{
    double z    = std::floor( m_julianDay - 1721118.5 );
    double r    = m_julianDay - 1721118.5 - z;
    double g    = z - 0.25;
    double a    = std::floor( g / 36524.25 );
    double b    = a - std::floor( a / 4 );

    m_year      = static_cast< int >( std::floor(( b + g ) / 365.25 ));
    double c    = b + z - std::floor( 365.25 * m_year);
    auto month  = static_cast< int >( std::floor( ( 5 * c + 456 ) / 153 ));
    double dday = c - std::floor(( 153.0 * month - 457 ) / 5) + r;
    auto day    = static_cast< int >( dday );

    if ( month > 12 ) {
        ++ m_year;
        month -= 12;
    }
    r               *= 24;
    auto hour        = static_cast< int >( std::floor( r ));
    r               -= std::floor(r);
    r               *= 60;
    auto minute      = static_cast< int >( std::floor( r ));
    r               -= std::floor( r );
    r               *= 60;
    auto second      = static_cast< int >( std::floor( r ));
    r               -= std::floor(r);
    r               *= 1000;
    auto msec        = static_cast< int >( std::floor( r ));
    r               -= std::floor( r );
    r               *= 1000;
    auto usec        = static_cast< int >( r + 0.5 );


    //Adjustment for overflows...
    if ( day > daysInMonth( m_year, month )) {
        day -= daysInMonth( m_year, month );
        if (++ month > 12) {
            ++ m_year;
            month -= 12;
        }
    }
    m_month     = static_cast< Month >( month );
    m_day       = DayOfMonthType( day );
    m_hour      = HourType( hour );
    m_minute    = MinuteType( minute );
    m_second   = SecondType( second );
    m_msec     = MilliSecType( msec );
    m_usec     = MicroSecType( usec );
}




//********************************** IMPL ************************************/

DateTime::DateTime( const Timestamp &timestamp )
    : m_data( std::make_unique< DateTime::Data >( timestamp.toUTCMicroSec() ))
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
    return m_data->year();
}


Month DateTime::month() const
{
    return m_data->month();
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


bool DateTime::isLeapYear() const
{
    return ::Vq::isLeapYear( m_data->year() );
}


bool DateTime::operator == ( const DateTime &other ) const
{
    return m_data->val() == other.m_data->val();
}


bool DateTime::operator != ( const DateTime &other ) const
{
    return ! ( *this == other );
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

