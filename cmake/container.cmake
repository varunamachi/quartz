if( DEFINED VQ_PROJECT_DEFINED )
    message( FATAL_ERROR
             "Container is trying to be a project, which it should not do. "
             "Check if both quartz.cmake and container.cmake are included in "
             "a single CMakeLists.txt" )
endif()
set( VQ_IS_PROJECT_CONTAINER ON )

set( VQ_BUILD_DIR       $ENV{QUARTZ_ROOT}/builds )
set( VQ_OUTPUT_DIR      $ENV{QUARTZ_ROOT}/output )
set( VQ_SRC_DIR         $ENV{QUARTZ_ROOT}/source )
set( VQ_TEST_DIR        $ENV{QUARTZ_ROOT}/tests )

set( CMAKE_INSTALL_PREFIX  ${VQ_OUTPUT_DIR} )

macro( add_project MODULE_NAME )
    add_subdirectory( ${MODULE_NAME} )
endmacro()

