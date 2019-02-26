project( common )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_qt()
qz_add_core()

add_definitions( -DQUARTZ_COMMON )
#SET(CMAKE_CXX_STANDARD 14)

vq_headers(
    QuartzCommon.h
    stdafx.h
)

add_subdirectory( generic_config )
add_subdirectory( widgets )
add_subdirectory( templating )
add_subdirectory( model_view )
add_subdirectory( iconstore )

vq_create_sharedlib()
vq_install()

message( STATUS  )
