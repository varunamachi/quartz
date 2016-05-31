
#pragma once

#include <algorithm>
#include <limits>

namespace Vq {

template< typename T,
          T MIN = std::numeric_limits< T >::min(),
          T MAX = std::numeric_limits< T >::max(),
          typename = typename std::enable_if<
              std::is_integral< T >::value >::type >
class ConstrainedValue
{
public:
    using ThisType = ConstrainedValue< T, MIN, MAX >;

    constexpr ConstrainedValue( T value )
        : m_value( value )
    {
        static_assert( value <= MAX, "Value is more than maximum allowed" );
        static_assert( value >= MIN, "Value is less than minimum allowed" );
        m_value = ( m_value >= MIN ? ( m_value <= MAX ? m_value
                                                      : MAX )
                                   : MIN );
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename std::enable_if< std::is_same< T, OType >::value >::type >
    constexpr ConstrainedValue(
            const ConstrainedValue< OType, O_MIN, O_MAX > &other )
        : m_value( other.value() )
    {
        staticBoundCheck< OType, O_MIN, O_MAX >();
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename std::enable_if< std::is_same< T, OType >::value >::type >
    ThisType & operator = ( const ConstrainedValue< OType, O_MIN, O_MAX> &other)
    {
        staticBoundCheck< OType, O_MIN, O_MAX >();
        m_value = other.value();
        return this;

        //Do the same for other operators...
    }

    constexpr T max() const
    {
        return MAX;
    }

    constexpr T min() const
    {
        return MIN;
    }

    constexpr T value() const
    {
        return  m_value;
    }

    constexpr explicit operator T () const {
        return m_value;
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX >
    constexpr bool operator == (
            const ConstrainedValue< OType, O_MIN, O_MAX > &other ) {
        return std::is_same< T, OType >::value
                && MIN == O_MIN
                && MAX == O_MAX
                && m_value == other.value();
    }

private:
    template< typename OType, OType O_MIN, OType O_MAX >
    constexpr void staticBoundCheck()
    {
        static_assert( MIN <= O_MIN,
                       "Passed type can't MIN less than that of this type" );
        static_assert( MAX >= O_MAX,
                       "Passed type can't MAX less than that of this type" );
    }

    T m_value;
};




}
