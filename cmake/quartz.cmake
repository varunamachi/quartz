file( TO_CMAKE_PATH "$ENV{QUARTZ_ROOT}" QUARTZ_ROOT )

set( CMAKE_MODULE_PATH "${QUARTZ_ROOT}/cmake" ${CMAKE_MODULE_PATH} )
set (CMAKE_CXX_STANDARD 14)

set( PROJECT_ROOT ${QUARTZ_ROOT} )
include( ${QUARTZ_ROOT}/cmake/DeployQt5.cmake)
include( ${QUARTZ_ROOT}/cmake/cmake_lib/core.cmake)

macro( qz_add_core )
    vq_add_module( "core" )
endmacro( qz_add_core )


macro( qz_add_common )
    vq_add_module( "common" )
endmacro( qz_add_common )

macro( qz_add_base )
    vq_add_module( "base" )
endmacro()

macro( qz_add_resource QRC_FILE )
    qt5_add_resources( RES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${QRC_FILE} )
    vq_add_prop( ${PROJECT_NAME}_SRC "${RES_FILE}" )
endmacro()

macro( qz_add_qt_modules )
    foreach( MODULE_NAME ${ARGV} )
        find_package( "Qt5${MODULE_NAME}" )
        list( APPEND VQ_INCLUDE_DIRS ${Qt5${MODULE_NAME}_INCLUDE_DIRS} )
        list( APPEND VQ_LIBS_DEBUG Qt5::${MODULE_NAME} )
        list( APPEND VQ_LIBS_RELEASE Qt5::${MODULE_NAME} )
    endforeach()
endmacro()

macro( qz_add_qt )
    set( CMAKE_AUTOMOC ON )
    set( CMAKE_AUTOUIC ON )
    set( CMAKE_AUTORCC ON )
    set( CMAKE_INCLUDE_CURRENT_DIR ON )
    qz_add_qt_modules(
        Widgets
        Sql
        Xml
        Quick
        QuickWidgets
        Svg
        Network
        Sql

    )
endmacro( qz_add_qt )

macro( qz_install )
    vq_install()
    if (WIN32)
        find_package( "Qt5Core" )
        get_filename_component(QT5_BINARY_DIR
                               "${QT_QMAKE_EXECUTABLE}"
                               DIRECTORY)
        set(${WinDep} "${QT5_BINARY_DIR}/windeployqt.exe")
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND set PATH=%PATH%$<SEMICOLON>"${QT5_BINARY_DIR}"
            COMMAND "windeployqt"
                --dir "${CMAKE_CURRENT_BINARY_DIR}"
                -xml
                -sql
                -serialport
                -webengine
                -webchannel
                -webenginewidgets
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        )
    endif()
endmacro( qz_install )




