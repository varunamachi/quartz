#pragma once

#include <memory>
#include <string>

#include "../../common/Result.h"
#include "../../common/Macros.h"

namespace Vq
{

class SharedLibrary
{
public:
    VQ_NO_COPY( SharedLibrary );

    using LibraryFunction = void * ( * )();

    explicit SharedLibrary( const std::string & libPath );

    SharedLibrary( SharedLibrary &&other );

    SharedLibrary & operator = ( SharedLibrary &&other );

    ~SharedLibrary();

    bool operator == ( const SharedLibrary &other );

    Result< bool > load();

    Result< bool > unload();

    Result< SharedLibrary:: LibraryFunction > resolve(
            const std::string &symbolName );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

}
