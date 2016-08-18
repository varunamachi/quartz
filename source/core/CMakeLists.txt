project( core )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

vq_add_qt()

add_definitions( -DQUARTZ_CORE )

vq_headers(
    QuartzCore.h
    Convenience.h
)


vq_classes(
    JobManager
)

add_subdirectory( logger )
add_subdirectory( utils )

vq_create_sharedlib()
vq_install()
