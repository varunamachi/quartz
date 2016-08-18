project( quartz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_common()
vq_add_qt()

#TODO this is a hack for now to fix build errors
#add_definitions( -DQUARTZ_CORE )

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

vq_create_app()
vq_install()
