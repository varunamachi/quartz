#pragma once

#include <functional>

class QVariant;
class QString;

namespace Quartz {

class AbstractConfigLoader
{

public:
    using StoreFunc = std::function< void( const QString &,
                                           const QString &,
                                           const QVariant & )>;



    StoreFunc storeFunc() const;

    virtual bool load( const QString &filePath ) const = 0;

protected:
    explicit AbstractConfigLoader( StoreFunc storeFunc );

    virtual ~AbstractConfigLoader() { }

private:
    StoreFunc m_storeFunc;

};

}
