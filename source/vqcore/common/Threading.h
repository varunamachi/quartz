#pragma once

#include "Macros.h"

#include <mutex>
#include <thread>


#define VQ_LOCK( mtx ) \
    std::lock_guard< std::mutex > LINE_VAR( guard )( mtx )
