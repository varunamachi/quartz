#pragma once

#include <functional>
#include <QByteArray>

class QVariant;
class QString;

namespace Quartz {

class AbstractConfigLoader
{

public:
    using StoreFunc = std::function< void( const QString &,
                                           const QString &,
                                           const QVariant & )>;



    StoreFunc storeFunc() const
    {
        return m_storeFunc;
    }

    virtual bool load( const QByteArray content ) const = 0;

    virtual ~AbstractConfigLoader() { }

protected:
    explicit AbstractConfigLoader( StoreFunc storeFunc )
        : m_storeFunc( storeFunc )
    {

    }


private:
    StoreFunc m_storeFunc;

};

}
