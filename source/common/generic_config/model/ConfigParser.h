#pragma once

#include <memory>

#include <QVector>

#include "../../QuartzCommon.h"

class QByteArray;
class QDomElement;

namespace Quartz {

class Config;
class Param;
class Param;
class Group;

class QUARTZ_COMMON_API ConfigParser
{
public:
    ConfigParser();

    virtual ~ConfigParser();

    QVector< std::shared_ptr< Config >> parse( const QByteArray &content );

    std::unique_ptr< Config > parse( const QDomElement &configRoot );


protected:
    std::shared_ptr< Param > parseParam( const QDomElement &paramNode );

    std::shared_ptr< Group > parseGroup(
            Config &config,
            const QDomElement &groupNode );

};

}
