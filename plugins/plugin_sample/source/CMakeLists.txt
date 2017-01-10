project( plugin_sample )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

add_definitions( -DSAMPLE_PLUGIN )

set( CMAKE_AUTORCC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

vq_add_qt()
qz_add_plugin_base()
qz_add_common()
qz_add_base()
qz_add_core()

vq_sources(
    SamplePlugin.cpp
    sample.qrc
)

vq_headers(
    Sample.h
)

vq_classes(
    TitleItemProvider
    ViewProvider
    NodeProvider
    ContentProvider
    PluginBundle
)

vq_dump_vars()

qz_create_plugin()
qz_install_plugin()



