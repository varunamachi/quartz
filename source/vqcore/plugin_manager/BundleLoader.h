#pragma once

#include <memory>
#include <unordered_map>

#include "../Vq.h"
#include "../common/Macros.h"
#include "../common/Result.h"




namespace Vq {

class BundleLibrary;
using BundleLibraryPtrUq = std::unique_ptr< BundleLibrary >;
using BundleMap = std::unordered_map<
                    std::string,
                    BundleLibraryPtrUq >;

class VQ_API BundleLoader
{
public:


    Result< BundleMap > loadAll( const std::string & location );

    Result< BundleLibraryPtrUq > loadFile( const std::string &filePath );

private:


};

}
