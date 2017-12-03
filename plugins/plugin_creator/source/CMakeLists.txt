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
    EntryPoint.cpp
)

vq_classes(
    Plugin
    NodeProvider
    ContentProvider
    CreatorWidget
    TemplateManager
    AbstractTemplateProvider
    TemplateSelectorDialog
    GenInfo
    CodeGenerator
    TemplateConfigWidget
)

#vq_interfaces(
#    TreeNode
#)

add_subdirectory( resources )

qz_create_plugin()
qz_install_plugin()



