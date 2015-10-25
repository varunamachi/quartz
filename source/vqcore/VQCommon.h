#pragma once

#include <functional>

namespace Vam {

class ScopedOperation
{
public:
    ScopedOperation( std::function< void() > entry,
                     std::function< void() > exit )
        : m_exitTask( exit )
    {
        if( entry != nullptr ) {
            entry();
        }
    }

    ~ScopedOperation()
    {
        if( m_exitTask ) {
            m_exitTask();
        }
    }

private:
    std::function< void() > m_exitTask;
};

}


#define TOKENPASTE( x, y ) x##y
#define TOKENPASTE2( x, y ) TOKENPASTE( x, y )
#define UNK( n ) TOKENPASTE2( n, __LINE__ )

#define AT_SCOPE_EXIT( x ) \
    Vam::ScopedOperation UNK( tnt_scpop )( nullptr, [ & ]() { x; })

#define SCOPE_LIMIT( x, y ) \
    Vam::ScopedOperation UNK( tnt_scpop )( [ & ]() { x; },  \
                                           [ & ]() { y; })


#define VQ_INTERFACE struct
#define VQ_SCOPE( _zed )

#define VQ_OUT
#define VQ_IN_OUT
