#pragma once

#include <memory>
#include <string>

#include "../../common/Result.h"

namespace Vq
{

class SharedLibrary
{
public:
    using LibraryFunction = void ( * )();

    explicit SharedLibrary( const std::string & libPath );

    ~SharedLibrary();

    Result< bool > load();

    Result< bool > unload();

    Result< SharedLibrary:: LibraryFunction > resolve(
            const std::string &symbolName );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

}
