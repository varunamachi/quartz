project( plugin_sample )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

add_definitions( -DSAMPLE_PLUGIN )

qz_add_core()
qz_add_base()
qz_add_common()
vq_add_qt()

vq_sources(
    SamplePlugin.cpp
)

vq_headers(
    Sample.h
)

vq_classes(
    TitleItemProvider
    ViewProvider
    NodeProvider
    ContentProvider
)

vq_dump_vars()

qz_create_plugin()
qz_install_plugin()



