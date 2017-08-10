#pragma once

#include <memory>

class QByteArray;

namespace Quartz {

class Config;

class ConfigParser
{
public:
    std::unique_ptr< Config > parse( const QByteArray &content );

private:

};


}
