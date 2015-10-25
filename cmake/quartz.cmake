include( $ENV{QUARTZ_ROOT}/cmake/DeployQt5.cmake)

set( VQ_BUILD_DIR       $ENV{QUARTZ_ROOT}/builds )
set( VQ_OUTPUT_DIR      $ENV{QUARTZ_ROOT}/output )
set( VQ_SRC_DIR         $ENV{QUARTZ_ROOT}/source )
set( VQ_TEST_DIR        $ENV{QUARTZ_ROOT}/tests )

include( $ENV{QUARTZ_ROOT}/cmake/vqcore.cmake)

macro( qz_add_vqcore )
    vq_add_module( "quartz" "vqcore" )
endmacro( qz_add_vqcore )

macro( qz_add_core )
    qz_add_vqcore()
    vq_add_module( "quartz" "quartz_core" )
endmacro( qz_add_core )


macro( qz_add_common )
    qz_add_core()
    vq_add_module( "quartz" "quartz_common" )
endmacro( qz_add_common )
