project( quartz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_common()
vq_add_qt()


vq_classes (
    QuartzWindow
    ActionBar
    TitleBar
    PageManager
    PluginManager
    BundleLoader
    ViewManager
    WelcomePage
)

vq_sources(
    quartz.cpp
)

add_subdirectory( adapted )

vq_create_app()
vq_install_bin()

message( STATUS  )
