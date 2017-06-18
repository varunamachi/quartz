project( plugin_creator )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

qz_add_qt()
qz_add_plugin_base()
qz_add_common()
qz_add_base()
qz_add_core()

qz_add_resource( creator.qrc )

vq_sources(
    CreatorPlugin.cpp
)

vq_classes(
    NodeProvider
    ContentProvider
    PluginBundle
    CreatorWidget
    Template
    TemplateManager
    AbstractTemplateProvider

)

add_subdirectory( resources )

qz_create_plugin()
qz_install_plugin()



