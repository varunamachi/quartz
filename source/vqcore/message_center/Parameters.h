
#pragma once

#include <QHash>
#include <QVariant>

#include "../VQ.h"

namespace Vam {

class VQ_CORE_EXPORT Parameters
{
public:
    Parameters( QHash< QString, QVariant > &params );

    void addParam( const QString &key, const QVariant &value );

    void removeParam( const QString &key );

    const QVariant param( const QString &key ) const;

private:
    QHash< QString, QVariant > m_params;

};

}
