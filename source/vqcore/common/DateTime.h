
#pragma once

#include <cstdint>
#include <memory>

namespace Vq {

//Inspired by Poco::DateTime

class Timestamp;

enum class Month : std::uint8_t
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};


enum class Day : std::uint8_t
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

class DateTime
{
public:
    explicit DateTime( const Timestamp &timestamp );

    DateTime( const DateTime &other );

    DateTime( DateTime &&other );

    ~DateTime();

    DateTime & operator = ( const DateTime &other );

    DateTime & operator = ( const DateTime &&other );

    int year() const;

    Month month() const;

    int week( Day firstDayOfWeek = Day::Monday ) const;

    Day dayOfWeek() const;

    int dayOfMonth() const;

    int dayOfYear() const;

    int hour() const;

    int minute() const;

    int second() const;

    int millisecond() const;

    int microsecond() const;

    Timestamp timestamp() const;

    bool operator == ( const DateTime &other ) const;

    bool operator != ( const DateTime &other ) const;

    bool operator <  ( const DateTime &other ) const;

    bool operator <= ( const DateTime &other ) const;

    bool operator >  ( const DateTime &other ) const;

    bool operator >= ( const DateTime &other ) const;

    DateTime operator + ( const DateTime &other );

    DateTime operator - ( const DateTime &other );

    DateTime & operator += ( const DateTime &other );

    DateTime & operator -= ( const DateTime &other );

    static DateTime now();

private:
    class Data;
    std::unique_ptr< Data > m_data;

};


}
