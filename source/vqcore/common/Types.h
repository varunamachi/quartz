#pragma once

#include <functional>

#include "Result.h"

namespace Vq {

using ProgressFunction = std::function< bool( std::uint8_t progress )>;
using DetailedProgressFunc
    = std::function< bool( std::size_t, std::size_t )>;

}
