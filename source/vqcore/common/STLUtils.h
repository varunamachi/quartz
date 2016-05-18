#pragma once

#include <cstdint>
#include <functional>
#include <algorithm>

#include "Macros.h"

namespace Vam { namespace STLUtils {


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


    template< typename ContainerType >
    void multiRemove( ContainerType &container,
                      const typename ContainerType::key_type &key,
                      const typename ContainerType::value_type &value )
    {
//        auto rangeIt = container.equal_range( key );

    }


} }
