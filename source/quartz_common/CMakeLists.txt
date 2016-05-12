project( quartz_common )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

vq_add_qt()
qz_add_vqcore()

add_definitions( -DQUARTZ_COMMON )


add_subdirectory( generic_config )
add_subdirectory( widgets )

vq_create_sharedlib()
vq_install()

message( STATUS  )
