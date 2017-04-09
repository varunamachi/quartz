project( plugin_serial_console )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )
include( $ENV{QUARTZ_ROOT}/cmake/plugins.cmake )

qz_add_qt()
qz_add_qt_modules( SerialPort )
qz_add_plugin_base()
qz_add_common()
qz_add_base()
qz_add_core()

qz_add_resource( serial_console.qrc )

add_subdirectory( resources )

vq_sources(
    SerialConsole.cpp
)

vq_classes(
    PluginBundle
    ContentProvider
    NodeProvider
    ConsoleWidget
    MainWidget
    SettingsDialog
    SerialSettings
)

qz_create_plugin()
qz_install_plugin()
