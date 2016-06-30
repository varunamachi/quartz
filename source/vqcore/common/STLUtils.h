#pragma once

#include <cstdint>
#include <functional>
#include <algorithm>

#include "Macros.h"

namespace Vq { namespace STLUtils {

template< typename... Ts >
struct EvalHelper
{
    using type = void;
};


template< typename ContainerType >
struct IsStdContainer
{
    template< typename U,
              typename  = typename EvalHelper<
                  typename U::value_type,
                  typename U::iterator,
                  decltype( std::declval< U >().begin() ),
                  decltype( std::declval< U >().end() ) >::type >
    static constexpr bool test( int /*unused*/ )
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
    template< typename U,
              typename = typename EvalHelper <
                  typename U::key_type,
                  typename U::value_type >::type >
    static constexpr bool test( int /*unused*/ )
    {
        return IsStdContainer< U >::value;
    }

    template< typename U > static constexpr bool test( ... )
    {
        return false;
    }

    static constexpr bool value = test< ContainerType >( int () );
};


template< typename ContainerType >
struct IsSequentialContainer
{
    static constexpr bool value = IsStdContainer< ContainerType >::value
            && ( ! IsAssociativeContainer< ContainerType >::value );

};


template< typename ContainerType,
          typename = typename std::enable_if<
              IsAssociativeContainer< ContainerType >::value >::type >
bool contains( const ContainerType &container,
               const typename ContainerType::key_type &key )
{
    auto it = container.find( key );
    return it != std::end( container );
}


template< typename ContainerType,
          typename = typename std::enable_if<
              IsSequentialContainer< ContainerType >::value >::type >
bool contains( const ContainerType &container,
               const typename ContainerType::value_type &elem )
{
    auto it = std::find( std::begin( container ),
                         std::end( container ),
                         elem );
    bool result = it != std::end( container );
    return result;
}


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


template< typename ContainerType,
          typename = typename std::enable_if<
              IsSequentialContainer< ContainerType >::value >::type >
void remove( ContainerType &container,
             const typename ContainerType::value_type &item )
{
    auto it = std::remove( std::begin( container ),
                           std::end( container ),
                           item );
    container.erase( it, std::end( container ));
}


template< typename ContainerType >
void remove( ContainerType &container,
             const typename ContainerType::mapped_type &item )
{
    auto it = std::remove_if(
                std::begin( container ),
                std::end( container ),
                [ &item ]( typename ContainerType::value_type &pair ) {
        return pair->second == item;
    });
    container.erase( it, std::end( container ));
}


template< typename ContainerType >
void remove( ContainerType &container,
             const typename ContainerType::key_type &key )
{
    container.erase( key );
}



//template< typename ContainerType >
//void multiRemove( ContainerType &/*container*/,
//                  const typename ContainerType::key_type &/*key*/,
//                  const typename ContainerType::value_type &/*value*/ )
//{
//          //        auto rangeIt = container.equal_range( key );

//}


} }
