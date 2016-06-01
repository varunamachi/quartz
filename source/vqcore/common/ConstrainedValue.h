
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
        : m_value( value >= MIN ? ( value <= MAX ? value : MAX ) : MIN )
    {
        static_assert( value <= MAX, "Value is more than maximum allowed" );
        static_assert( value >= MIN, "Value is less than minimum allowed" );

    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same< T, OType >::value >::type >
    constexpr ConstrainedValue(
            const ConstrainedValue< OType, O_MIN, O_MAX > &other )
        : m_value( other.value() )
    {
        static_assert( staticBoundCheck< OType, O_MIN, O_MAX >(),
                       "Static Bound Check Failed!!!" );
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same< T, OType >::value >::type >
    constexpr ConstrainedValue(
            const ConstrainedValue< OType, O_MIN, O_MAX > &&other )
        : m_value( other.value() )
    {
        static_assert( staticBoundCheck< OType, O_MIN, O_MAX >(),
                       "Static Bound Check Failed!!!" );
    }


    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same< T, OType >::value >::type >
    ThisType & operator = ( const ConstrainedValue< OType, O_MIN, O_MAX> &other)
    {
        static_assert( staticBoundCheck< OType, O_MIN, O_MAX >(),
                       "Static Bound Check Failed!!!" );
        m_value = other.value();
        return this;
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same< T, OType >::value >::type >
    ThisType & operator = ( ConstrainedValue< OType, O_MIN, O_MAX> &&other)
    {
        static_assert( staticBoundCheck< OType, O_MIN, O_MAX >(),
                       "Static Bound Check Failed!!!" );
        m_value = other.value();
        return this;
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
            const ConstrainedValue< OType, O_MIN, O_MAX > &other ) const {
        return std::is_same< T, OType >::value
                && MIN == O_MIN
                && MAX == O_MAX
                && m_value == other.value();
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX >
    constexpr bool operator != (
            const ConstrainedValue< OType, O_MIN, O_MAX > &other ) const {
        return ! ( *this == other );
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same < T, OType >::value >::type >
    constexpr bool operator > (
            const ConstrainedValue< OType, O_MIN, O_MAX > &other ) const {
        return m_value < static_cast< T >( other.value() );
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same < T, OType >::value >::type >
    constexpr bool operator >= (
            const ConstrainedValue< OType, O_MIN, O_MAX > &other ) const {
        return m_value >= static_cast< T >( other.value() );
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same < T, OType >::value >::type >
    constexpr bool operator <= (
            const ConstrainedValue< OType, O_MIN, O_MAX > &other ) const {
        return m_value <= static_cast< T >( other.value() );
    }

    template< typename OType,
              OType O_MIN,
              OType O_MAX,
              typename = typename std::enable_if<
                  std::is_same < T, OType >::value >::type >
    constexpr bool operator < (
            const ConstrainedValue< OType, O_MIN, O_MAX > &other ) const {
                return m_value < static_cast< T >( other.value() );
    }

private:
    template< typename OType, OType O_MIN, OType O_MAX >
    constexpr bool staticBoundCheck() const
    {
        static_assert( MIN <= O_MIN,
                       "Passed type can't MIN less than that of this type" );
        static_assert( MAX >= O_MAX,
                       "Passed type can't MAX less than that of this type" );
        return true;
    }

    T m_value;
};




}
