#pragma once

#include <cstdint>
#include <functional>
#include <algorithm>

#include "Macros.h"

namespace Vam { namespace ContainerOps {


    template< typename ContainerType >
    std::size_t eraseIf(
            ContainerType container,
            std::function< bool( const typename ContainerType::value_type & )> condition )
    {
        auto it = std::remove_if( std::begin( container ),
                                  std::end( container ),
                                  condition );
        container.erase( it, end );
    }


} }
