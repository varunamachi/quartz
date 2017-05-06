#pragma once

#include <memory>
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



    virtual ~AbstractConfigLoader();

    StoreFunc storeFunc() const;

    virtual bool load( const QByteArray content ) const = 0;

protected:
    explicit AbstractConfigLoader( StoreFunc storeFunc );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
