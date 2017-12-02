project( plugin_sample )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

add_definitions( -DSAMPLE_PLUGIN )

qz_add_qt()
qz_add_plugin_base()
qz_add_common()
qz_add_base()
qz_add_core()

qz_add_resource( sample.qrc )

vq_sources(
    EntryPoint.cpp
)

vq_classes(
    SamplePlugin
    TitleItemProvider
    ViewProvider
    NodeProvider
    ContentProvider
)

#vq_dump_vars()

qz_create_plugin()
qz_install_plugin()



