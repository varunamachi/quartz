project( quartz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )


qz_add_qt()
qz_add_core()
qz_add_common()
qz_add_base()



qz_add_resource( quartz.qrc )
vq_classes (
    QuartzFramelessWindow
    QuartzFramedWindow
    WelcomePage
    HoverMoveFilter
    QzMainWidget
    AboutDialog
)

vq_sources(
    quartz.cpp
    quartz.rc
)

add_subdirectory( resources )
add_subdirectory( adapted )
add_subdirectory( inbuilt )
add_subdirectory( bindings )

vq_create_app()
qz_install()
