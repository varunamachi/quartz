project( plugins )
cmake_minimum_required( VERSION 3.1 )
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/cmake_lib/container.cmake )

#TODO this is a hack for now to fix build errors
#add_definitions( -DQUARTZ_CORE )

file( GLOB DIRS RELEATIVE
        RELEATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/* )
foreach( PLUGIN_DIR ${DIRS} )
    if( IS_DIRECTORY "${PLUGIN_DIR}" )
        if( EXISTS "${PLUGIN_DIR}/source/CMakeLists.txt" )
            if( NOT ${PLUGIN_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
                message( STATUS "Adding plugin at ${PLUGIN_DIR}" )
                add_project( "${PLUGIN_DIR}/source" )
            endif()
        endif()
    endif()
endforeach()        
        
        
