project( vqcore )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

add_definitions( -DVQ_CORE )

vq_add_qt()

vq_headers(
    VQ.h
    VQCommon.h
)

add_subdirectory( logger )
add_subdirectory( common )

vq_create_staticlib()
vq_install_lib()
vq_install_headers()

message( STATUS  )
