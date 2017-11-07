#pragma once

#include <memory>

#include "../../QuartzCommon.h"

class QString;

namespace Quartz {

class Param;
class Group;

class QUARTZ_COMMON_API Config
{
public:
    Config( const QString &id, const QString &name );

    ~Config();

    const QString & id() const;

    const QString & name() const;

    int numChildParams() const;

    Param * childParamAt( int index ) const;

    void addChildParameter( std::shared_ptr< Param > param );

    int numGroups() const;

    Group * groupAt( int index ) const;

    void addGroup( std::shared_ptr< Group > group );

    const Param * param( const QString &id ) const;

    bool registerParam( Param *param );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
