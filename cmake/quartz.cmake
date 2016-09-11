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

macro( qz_add_qt )
    set( CMAKE_AUTOMOC ON )
    set( CMAKE_AUTOUIC ON )
    set( CMAKE_INCLUDE_CURRENT_DIR ON )
    find_package( Qt5Widgets )
    find_package( Qt5Sql)
    list( APPEND VQ_INCLUDE_DIRS
            ${Qt5Widgets_INCLUDE_DIRS}
            ${Qt5Sql_INCLUDE_DIRS})
    list( APPEND VQ_LIBS_DEBUG Qt5::Widgets )
    list( APPEND VQ_LIBS_RELEASE Qt5::Widgets )
    list( APPEND VQ_LIBS_DEBUG Qt5::Sql )
    list( APPEND VQ_LIBS_RELEASE Qt5::Sql )
endmacro( vq_add_qt )


