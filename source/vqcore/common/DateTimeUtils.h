
#pragma once

#include <string>

#include "Macros.h"

namespace Vq {

class DateTime;
class Timestatmp;

class DateTimeUtils
{
public:
    VQ_MAKE_STATIC( DateTimeUtils );

    static std::string format( const DateTime &dateTime,
                               const std::string &formatString = "" );

    static std::string format( const Timestatmp &timestamp,
                               const std::string &formatString = "" );

    static std::string formattedNow( const std::string &formatString = "" );

private:
};

}
