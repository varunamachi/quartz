
project( plugin_webtech )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

qz_add_qt()
qz_add_qt_modules("WebEngineCore" "WebEngineWidgets" "WebChannel")
qz_add_plugin_base()
qz_add_common()
qz_add_base()
qz_add_core()

qz_add_resource( resources.qrc )

vq_headers(
    EntryPoint.cpp
    Plugin.cpp
)
vq_headers(
    Plugin.h
)

vq_classes(
    MonacoEditor
    FileHandlerProvider
)

add_subdirectory(conf)

qz_create_plugin()
qz_install_plugin()
            
