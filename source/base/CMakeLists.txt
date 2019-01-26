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
    QzAppContext
)

add_subdirectory( theme )
add_subdirectory( title_bar )
add_subdirectory( page_manager)
add_subdirectory( view_manager )
add_subdirectory( action_bar )
add_subdirectory( content_manager )
add_subdirectory( selector )
add_subdirectory( general_selector )
add_subdirectory( settings )
add_subdirectory( extension_details )
add_subdirectory( main_menu )
add_subdirectory( explorer )

vq_create_sharedlib()
vq_install()
