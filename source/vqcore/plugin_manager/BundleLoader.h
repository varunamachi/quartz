#pragma once

#include <memory>

class std::string;

namespace Vam {

class BundleLibrary;

class VQ_CORE_EXPORT BundleLoader
{
public:
    QHash< std::string, BundleLibrary::Ptr > loadAll( const std::string & location );

    std::shared_ptr< BundleLibrary > loadFile( const std::string &filePath );

private:

};

}
