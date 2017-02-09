project( plugin_orek_client )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

add_definitions( -DOREK_CLIENT_PLUGIN )

qz_add_qt()
qz_add_plugin_base()
qz_add_common()
qz_add_base()
qz_add_core()

qz_add_resource( orek_client.qrc )

vq_sources(
    OrekClient.cpp
)

vq_classes(
    ContentProvider
    PluginBundle
)

add_subdirectory( qml )

#vq_dump_vars()

qz_create_plugin()
qz_install_plugin()



