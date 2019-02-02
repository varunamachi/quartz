project( qz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
set( PROJECT_ROOT $ENV{QUARTZ_ROOT} )
include( $ENV{QUARTZ_ROOT}/cmake/cmake_lib/container.cmake )

if(CMAKE_COMPILER_IS_GNUCXX)

#        "${CMAKE_CXX_FLAGS}
#         -std=c++14")
endif()

add_project( source )
add_project( plugins )


