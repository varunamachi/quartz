#pragma once

#include <memory>

class QString;


namespace Quartz {

class Param;

class Config
{
public:
    Config( const QString &id, const QString &name );

    ~Config();

    const QString & id() const;

    const QString & name() const;

    int numParams() const;

    const Param * paramAt( int index ) const;

    void addParameter( std::shared_ptr< Param > param );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
