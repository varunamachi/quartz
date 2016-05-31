
#pragma once

#include <algorithm>

namespace Vq {

template< typename T >
class ConstrainedValue
{
public:
    ConstrainedValue()
    {
        static_assert( false, "ConstrainedValue only supports integrals" );
    }

private:
};


template< typename T,
          int MIN,
          int MAX,
          typename std::enable_if< std::is_integral< T >::value >::type >
class ContstrainedValue
{
public:
    constexpr ContstrainedValue( T value )
        : m_value( value )
    {
        static_assert( value <= MAX, "Value is more than maximum allowed" );
        static_assert( value >= MIN, "Value is less than minimum allowed" );
        if( m_value < MIN ) {
            m_value = MIN;
        }
        else if( m_value > MAX ){
            m_value = MAX;
        }
        //no exception - C++14
    }


private:
    const T m_value;
};




}
