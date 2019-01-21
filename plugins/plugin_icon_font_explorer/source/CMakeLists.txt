
project( plugin_icon_font_explorer )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

qz_add_qt()
qz_add_plugin_base()
qz_add_common()
qz_add_base()
qz_add_core()

qz_add_resource( resources.qrc )

vq_classes(
    MainWidget
    IconView
    IconDelegate
    IconDetails
    IconNode
    IconProxyModel
)

vq_headers(
    ContentProvider.cpp
    EntryPoint.cpp
    NodeProvider.cpp
    Plugin.cpp
)
vq_headers(
    ContentProvider.h
    NodeProvider.h
    Plugin.h
    resources.qrc
)

qz_create_plugin()
qz_install_plugin()
            
