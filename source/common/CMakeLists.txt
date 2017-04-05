project( common )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_qt()
qz_add_core()

add_definitions( -DQUARTZ_COMMON )

vq_headers(
    QuartzCommon.h
)

add_subdirectory( generic_config )
add_subdirectory( widgets )
add_subdirectory( templating )

vq_create_sharedlib()
vq_install()

message( STATUS  )
