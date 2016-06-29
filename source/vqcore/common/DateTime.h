
#pragma once

#include <cstdint>
#include <memory>

#include "ConstrainedValue.h"

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

using DayOfMonthType = ConstrainedValue< int, 1, 31 >;
using DayOfYearType  = ConstrainedValue< int, 1, 365 >;
using WeekOfYearType = ConstrainedValue< int, 1, 53 >;
using HourType       = ConstrainedValue< int, 0, 23 >;
using MinuteType     = ConstrainedValue< int, 1, 59 >;
using SecondType     = ConstrainedValue< int, 0, 59 >;
using MilliSecType   = ConstrainedValue< int, 0, 999 >;
using MicroSecType   = ConstrainedValue< int, 0, 999 >;



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

    WeekOfYearType week( Day firstDayOfWeek = Day::Monday ) const;

    Day dayOfWeek() const;

    DayOfMonthType dayOfMonth() const;

    DayOfYearType dayOfYear() const;

    HourType hour() const;

    MinuteType minute() const;

    SecondType second() const;

    MilliSecType millisecond() const;

    MicroSecType microsecond() const;

    Timestamp timestamp() const;

    bool isLeapYear() const;

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
