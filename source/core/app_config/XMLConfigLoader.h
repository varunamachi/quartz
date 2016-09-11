#pragma once

#include <memory>

#include "IConfigBatchLoader.h"

namespace Quartz {

class XMLConfigLoader : public IConfigBatchLoader
{
public:
    explicit XMLConfigLoader( const QString &filePath );

    ~XMLConfigLoader();

    void load( StoreFunc storeFunc ) override;



private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};







}
