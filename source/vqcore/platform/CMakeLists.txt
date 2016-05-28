
include( $ENV{QUARTZ_ROOT}/cmake/platform.cmake )

add_subdirectory( file_system )
add_subdirectory( shared_library )

vq_headers(
    Platform.h
)

