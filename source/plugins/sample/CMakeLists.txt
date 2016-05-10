project( sample )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_vqcore()
qz_add_core()
vq_add_qt()

vq_sources(
    SampleBundleInterface.cpp
)

vq_classes(
    SampleBundle
    PagePlugin
    TitleBarPlugin
)

vq_create_sharedlib()



