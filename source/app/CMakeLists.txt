project( quartz )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_common()
vq_add_qt()


vq_headers (
    QuartzWindow.h
    ActionBar.h
    TitleBar.h
    PageManager.h
    PluginManager.h
    BundleLoader.h
    QuartzComponent.h
)

vq_sources(
    quartz.cpp
    QuartzWindow.cpp
    TitleBar.cpp
    ActionBar.cpp
    PageManager.cpp
    PluginManager.cpp
    BundleLoader.cpp
    QuartzComponent.cpp
)

vq_create_app()
vq_install_bin()

message( STATUS  )
