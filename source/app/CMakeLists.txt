project( quartz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )


qz_add_qt()
qz_add_core()
qz_add_common()
qz_add_base()



vq_classes (
    QuartzFramelessWindow
    QuartzFramedWindow
    WelcomePage
    HoverMoveFilter
    QzMainWidget
)

vq_sources(
    quartz.cpp
)

add_subdirectory( adapted )
add_subdirectory( inbuilt )
add_subdirectory( bindings )

#vq_dump_vars()

vq_create_app()
vq_install()
