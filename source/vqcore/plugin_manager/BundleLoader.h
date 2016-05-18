#pragma once

#include <memory>
#include <unordered_map>

#include "../VQ.h"
#include "../common/Macros.h"




namespace Vam {

class BundleLibrary;

class VQ_CORE_EXPORT BundleLoader
{
public:
    using BundleMap = std::unordered_map<
                        std::string,
                        std::unique_ptr< BundleLibrary >>;


    std::size_t loadAll( const std::string & location,
                         VQ_OUT BundleMap &bundlesOut );

    std::unique_ptr< BundleLibrary > loadFile( const std::string &filePath );

private:

};

}
