#pragma once

#include <memory>

#include <QString>
#include <QList>

#include "Param.h"

namespace Vq { namespace Quartz {

class Config
{
public:
    typedef std::shared_ptr< Config > Ptr;

    Config( const QString &id, const QString &name )
        : m_id( id )
        , m_name( name )
    {

    }

    const QString & id() const
    {
        return m_id;
    }

    const QString & name() const
    {
        return m_name;
    }

    const QList< Param::Ptr > & params() const
    {
        return m_params;
    }

    void addParameter( Param::Ptr param )
    {
        m_params.push_back( param );
    }

private:
    QString m_id;

    QString m_name;

    QList< Param::Ptr > m_params;
};

} }
