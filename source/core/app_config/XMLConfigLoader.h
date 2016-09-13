#pragma once

#include <memory>

#include "AbstractConfigLoader.h"

namespace Quartz {

class XMLConfigLoader : public AbstractConfigLoader
{
public:
    explicit XMLConfigLoader( StoreFunc storeFunc );

    ~XMLConfigLoader();

    bool load( const QString &filePath ) const override;

};







}
