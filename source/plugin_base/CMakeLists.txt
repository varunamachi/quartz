project( plugin_base )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_base()
qz_add_core()
qz_add_qt()


vq_classes(
    BundleContext
)

vq_headers(
    PluginLogging.h
)


vq_create_staticlib()
vq_install()

