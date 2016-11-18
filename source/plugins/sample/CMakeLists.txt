project( sample )
cmake_minimum_required( VERSION 3.1 )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )


qz_add_core()
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
)

vq_dump_vars()

vq_create_sharedlib()



