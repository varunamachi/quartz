

#include "Timestamp.h"

namespace Vq {


Timestamp::Timestamp( const TimeVal &timeVal ) {

}



Timestamp::Timestamp( const Timestamp &other ) {

}



Timestamp::Timestamp( Timestamp &&other ) {

}


Timestamp & Timestamp::operator = ( const Timestamp &other ) {

}


Timestamp & Timestamp::operator = ( const Timestamp &&other ) {

}


bool Timestamp::operator == ( const Timestamp &other ) {

}


bool Timestamp::operator != ( const Timestamp &other ) {

}


bool Timestamp::operator >  ( const Timestamp &other ) {

}


bool Timestamp::operator >= ( const Timestamp &other ) {

}


bool Timestamp::operator <  ( const Timestamp &other ) {

}


bool Timestamp::operator <= ( const Timestamp &other ) {

}


Timestamp Timestamp::operator + ( const Timestamp &other ) {

}


Timestamp Timestamp::operator - ( const Timestamp &other ) {

}


Timestamp & Timestamp::operator += ( const Timestamp &other ) {

}


Timestamp & Timestamp::operator -= ( const Timestamp &other ) {

}


Timestamp::TimeVal Timestamp::toUTCMicroSec() const  {

}


Timestamp::TimeVal Timestamp::toPosixMicroSec() const  {

}


Timestamp Timestamp::now() {

}


Timestamp Timestamp::fromPosixEpoch( const std::time_t &time ) {

}


Timestamp Timestamp::fromUTCTime( const TimeVal &utc ) {

}

}
