project( base )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_qt()

qz_add_core()
qz_add_common()

add_definitions( -DQUARTZ_BASE )

vq_headers(
    QuartzBase.h
)


vq_classes(
)

add_subdirectory( theme )
add_subdirectory( title_bar )
add_subdirectory( page_manager)
add_subdirectory( view_manager )
add_subdirectory( action_bar )

vq_create_sharedlib()
vq_install()
