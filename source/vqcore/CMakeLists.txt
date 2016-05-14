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

add_subdirectory( common )
add_subdirectory( logger )
add_subdirectory( job_handler )
add_subdirectory( config_storage )
add_subdirectory( plugin_manager )
add_subdirectory( message_center )

vq_create_sharedlib()
vq_install()

message( STATUS  )
