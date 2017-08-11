#pragma once

#include <memory>

class QByteArray;
class QDomElement;

namespace Quartz {

class Config;
class Param;
class Param;
class Group;

class ConfigParser
{
public:
    std::unique_ptr< Config > parse( const QByteArray &content );

    std::unique_ptr< Config > parse( const QDomElement &configRoot );

    std::shared_ptr< Param > parseParam( const QDomElement &paramNode );

    std::shared_ptr< Group > parseGroup( const QDomElement &groupNode );
};

}
