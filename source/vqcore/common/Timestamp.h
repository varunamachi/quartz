
#pragma once

#include <cstdint>
#include <memory>
#include <ctime>

namespace Vq {


//Inspired by Poco::Timestamp
class Timestamp
{
public:
    using TimeVal = std::uint64_t;

    static const TimeVal TIMEVAL_MAX;

    static const TimeVal TIMEVAL_MIN;

    Timestamp() = delete;

    explicit Timestamp( const TimeVal &timeVal );

    Timestamp( const Timestamp &other );

    Timestamp( Timestamp &&other );

    ~Timestamp();

    Timestamp & operator = ( const Timestamp &other );

    Timestamp & operator = ( const Timestamp &&other );

    bool operator == ( const Timestamp &other );

    bool operator != ( const Timestamp &other );

    bool operator >  ( const Timestamp &other );

    bool operator >= ( const Timestamp &other );

    bool operator <  ( const Timestamp &other );

    bool operator <= ( const Timestamp &other );

    Timestamp operator + ( const Timestamp &other );

    Timestamp operator - ( const Timestamp &other );

    Timestamp & operator += ( const Timestamp &other );

    Timestamp & operator -= ( const Timestamp &other );

    TimeVal toUTCMicroSec() const;

    TimeVal toPosixMicroSec() const;

    TimeVal value() const;

    static Timestamp now();

    static Timestamp fromPosixEpoch( const std::time_t &time );

    static Timestamp fromUTCTime( const TimeVal &utc );

private:
    class Data;
    std::unique_ptr< Data > m_data;

};



}
