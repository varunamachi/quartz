file( TO_CMAKE_PATH "$ENV{QUARTZ_ROOT}" QUARTZ_ROOT )

set( PROJECT_ROOT ${QUARTZ_ROOT} )
include( ${QUARTZ_ROOT}/cmake/DeployQt5.cmake)
include( ${QUARTZ_ROOT}/cmake/cmake_lib/core.cmake)

macro( qz_add_core )
    vq_add_module( "quartz" "core" )
endmacro( qz_add_core )


macro( qz_add_common )
    vq_add_module( "quartz" "common" )
endmacro( qz_add_common )


macro( qz_install_plugin )

endmacro()
