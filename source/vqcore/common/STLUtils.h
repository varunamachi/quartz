#pragma once

#include <cstdint>
#include <functional>
#include <algorithm>

#include "Macros.h"

namespace Vq { namespace STLUtils {

template< typename ContainerType >
struct IsSTDContainer
{
    template< typename U > static constexpr
    decltype( std::declval< U::const_iterator >(), bool() )
        test( int /*unused*/ )
    {
        return true;
    }

    template< typename U > static constexpr bool test( ... )
    {
        return false;
    }

    static constexpr bool value = test< ContainerType >( int() );
};

template< typename ContainerType >
struct IsAssociativeContainer
{
    template< typename U > static constexpr
    decltype( std::declval< U::key_type >(),
              std::declval< U::value_type >(),
              bool() )
        test( int /*unused*/ )
    {
        return true;
    }

    template< typename U > static constexpr bool test( ... )
    {
        return false;
    }

    static constexpr bool value = test< ContainerType >( int() );
};


template< typename ContainerType,
          typename = typename std::enable_if
          <(
              ! IsAssociativeContainer< ContainerType >::value
              && IsSTDContainer< ContainerType >::value
          )>::type
        >
struct IsSequentialContainer : public std::true_type
{

};





template< typename ContainerType >
void eraseIf(
        ContainerType container,
        std::function< bool(
            const typename ContainerType::value_type & )> condition )
{
    auto it = std::remove_if( std::begin( container ),
                              std::end( container ),
                              condition );
    container.erase( it, std::end( container ));
}


template< typename ContainerType >
bool contains( const ContainerType &container,
               const typename ContainerType::key_type &key )
{
    auto it = container.find( key );
    return it != std::end( container );
}

//template< typename ContainerType,
//          std::enable_if< >
//          bool contains( const ContainerType &container )


template< typename ContainerType >
void multiRemove( ContainerType &/*container*/,
                  const typename ContainerType::key_type &/*key*/,
                  const typename ContainerType::value_type &/*value*/ )
{
          //        auto rangeIt = container.equal_range( key );

}


} }
