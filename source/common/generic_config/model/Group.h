#pragma once

#include <memory>

class QString;

namespace Quartz {

class Param;

class Group
{
public:
    Group( const QString &id,
           const QString &name,
           const QString &description );

    const QString & id() const;

    const QString & name() const;

    const QString & description() const;

    void addParam( std::shared_ptr< Param > param );

    Param * paramAt( int index ) const;

    void addSubGroup( std::shared_ptr< Group > subGroup );

    Group * subGroupAt( int index );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
