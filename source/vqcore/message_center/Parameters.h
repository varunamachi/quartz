
#pragma once

#include <QHash>
#include <QVariant>

#include "../VQ.h"

namespace Vam {

class VQ_CORE_EXPORT Parameters
{
public:
    Parameters( QHash< std::string, QVariant > &params );

    void addParam( const std::string &key, const QVariant &value );

    void removeParam( const std::string &key );

    const QVariant param( const std::string &key ) const;

private:
    QHash< std::string, QVariant > m_params;

};

}
