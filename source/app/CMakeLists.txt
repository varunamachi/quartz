project( quartz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )


vq_add_qt()

qz_add_core()
qz_add_common()



vq_classes (
    QuartzWindow
    ActionBar
    TitleBar
    PageManager
    ViewManager
    WelcomePage
    HoverMoveFilter
)

vq_sources(
    quartz.cpp
)

add_subdirectory( adapted )
add_subdirectory( interface )

vq_dump_vars()

vq_create_app()
vq_install()
