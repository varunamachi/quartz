if( DEFINED VQ_PROJECT_DEFINED )
    message( FATAL_ERROR
             "Container is trying to be a project, which it should not do. "
             "Check if both quartz.cmake and container.cmake are included in "
             "a single CMakeLists.txt" )
endif()
set( VQ_IS_PROJECT_CONTAINER ON )

file( TO_CMAKE_PATH "$ENV{QUARTZ_ROOT}" QUARTZ_ROOT )


set( VQ_BUILD_DIR       ${QUARTZ_ROOT}/builds )
set( VQ_OUTPUT_DIR      ${QUARTZ_ROOT}/output )
set( VQ_SRC_DIR         ${QUARTZ_ROOT}/source )
set( VQ_TEST_DIR        ${QUARTZ_ROOT}/tests )

set( CMAKE_INSTALL_PREFIX ${VQ_OUTPUT_DIR} )
set( SUBPROJECTS "" )

macro( add_project MODULE_NAME )
    add_subdirectory( ${MODULE_NAME} )
    set_property( GLOBAL APPEND PROPERTY "SUBPROJECTS"  ${MODULE_NAME} )
endmacro()

