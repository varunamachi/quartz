project( sfinae_one )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )


vq_sources(
	Main.cpp
)

vq_create_app()


message( STATUS  )
