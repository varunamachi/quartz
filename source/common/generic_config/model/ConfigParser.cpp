
#include <QByteArray>

#include "ConfigParser.h"
#include "Config.h"

namespace Quartz {

std::unique_ptr< Config > ConfigParser::parse( const QByteArray &content )
{
    if( content.isNull() ) {
        return nullptr;
    }
    std::unique_ptr< Config > config;

    return config;
}



}
