#pragma once

#include <memory>
#include <string>

#include "../../common/Result.h"
#include "../../common/Macros.h"

namespace Vq
{

class LibraryFunction
{
public:
    explicit LibraryFunction( void *funcPtr )
        : m_funcPtr( funcPtr )
    {

    }

    template< typename FuncSignature >
    FuncSignature get()
    {
        return reinterpret_cast< FuncSignature >( m_funcPtr );
    }

    template< typename RetType, typename... Ts >
    RetType operator()( Ts... args )
    {
        if( m_funcPtr != nullptr ) {
            return get< RetType( Ts... )>()( args... );
        }
        return RetType{ };
    }

private:
    void *m_funcPtr;
};

class SharedLibrary
{
public:
    VQ_NO_COPY( SharedLibrary );

    explicit SharedLibrary( const std::string & libPath );

    SharedLibrary( SharedLibrary &&other );

    SharedLibrary & operator = ( SharedLibrary &&other );

    ~SharedLibrary();

    bool operator == ( const SharedLibrary &other );

    Result< bool > load();

    Result< bool > unload();

    Result< LibraryFunction > resolve( const std::string &symbolName );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

}
