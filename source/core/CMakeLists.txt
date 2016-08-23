project( core )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

vq_add_qt()

add_definitions( -DQUARTZ_CORE )

vq_headers(
    QuartzCore.h
)


vq_classes(
)

add_subdirectory( logger )
add_subdirectory( utils )
add_subdirectory( job_manager )
add_subdirectory( extension_system )

vq_create_sharedlib()
vq_install()
