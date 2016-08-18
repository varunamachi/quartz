/*******************************************************************************
 * Copyright (c) 2014 Varuna L Amachi. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#pragma once

#include <functional>



#define TNT_NS1( x )            namespace x {
#define TNT_END_NS1( x )        }

#define TNT_NS2( x, y )         namespace x { namespace y {
#define TNT_END_NS2( y, x )     } }

#define TNT_NS3( x, y, z )      namespace x { namespace y { namespace z {
#define TNT_END_NS3( z, y, x )  } } }


#define QZ_INTERFACE struct

//To mark an argument as a out argument
#define TNT_OUT

//To mark an argument as a in-out argument
#define TNT_IN_OUT

namespace Tanyatu {

class ScopedOperation
{
public:
    ScopedOperation( std::function< void() > entry,
                     std::function< void() > exit )
        : m_exitTask( exit )
    {
        if( entry ) {
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

} //end of namespace Tanyatu

#define TOKENPASTE( x, y ) x##y
#define TOKENPASTE2( x, y ) TOKENPASTE( x, y )
#define UNK( n ) TOKENPASTE2( n, __LINE__ )

#define AT_SCOPE_EXIT( x ) \
    Tanyatu::ScopedOperation UNK( tnt_scpop )( 0, [ & ]() { x; })

#define SCOPE_LIMIT( x, y ) \
    Tanyatu::ScopedOperation UNK( tnt_scpop )( [ & ]() { x; },  \
                                                  [ & ]() { y; })


#define TNT_SCOPE
