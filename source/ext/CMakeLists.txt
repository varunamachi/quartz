project( ext )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

vq_add_qt()

add_definitions( -DQUARTZ_EXT )

vq_headers(
    QuartzExt.h
)

vq_interfaces(
    IQuartzPageManager
    IQuartzViewManager
    IQuartzActionBar
    IQuartzTitleBar
)

vq_classes(
    QuartzContext
    QuartzItem
)


vq_create_sharedlib()
vq_install()
