project( quartz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
set( PROJECT_ROOT $ENV{QUARTZ_ROOT} )
include( $ENV{QUARTZ_ROOT}/cmake/cmake_lib/container.cmake )

if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

add_project( core )
add_project( common )
add_project( base )
add_project( app )
add_project( plugins )



