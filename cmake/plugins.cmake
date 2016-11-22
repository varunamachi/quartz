
macro( qz_copy SOURCE DESTINATION )
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE} ${DESTINATION}
        COMMENT "Copying shared object ${SRC_PATH} to ${DST_PATH}" )
endmacro( qz_copy SOURCE DESTINATION )

macro( qz_create_plugin )
    vq_create_sharedlib()
    set_property( GLOBAL APPEND PROPERTY "PLUGIN_PATH"  ${PROJECT_NAME} )
endmacro( qz_create_plugin )


macro( qz_install_plugin )
    set( BTX "" )
    set( DIST_OUTPUT_DIR "bin/${CMAKE_BUILD_TYPE}/plugins/${PROJECT_NAME}" )
    set( BUILD_REL_DIR "plugins/${PROJECT_NAME}")
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set( BTX "d" )
        set( DIST_OUTPUT_DIR "${DIST_OUTPUT_DIR}/debug" )
        set( BUILD_REL_DIR "${BUILD_REL_DIR}/debug" )
    endif()
    set( PLUGIN_BIN_NAME "${VQ_LIB_PREFIX}${PROJECT_NAME}${BTX}${VQ_SO_EXT}" )
    install( TARGETS ${PROJECT_NAME} DESTINATION ${DIST_OUTPUT_DIR} )
    vq_get_prop( BUILT_WITH_APP "quartz_SUBPROJECT" )
    if( BUILT_WITH_APP )
        set( PLUGIN_DIR "${CMAKE_BINARY_DIR}/app/${BUILD_REL_DIR}" )
        set( SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_BIN_NAME}" )
        qz_copy( ${SOURCE} "${PLUGIN_DIR}/${PLUGIN_BIN_NAME}" )
    endif()
endmacro( qz_install_plugin )

#macro( qz_copy_plugins )
#    vq_get_prop( PLUGINS "PLUGINS" )
#    foreach( SRC_PATH ${PLUGINS} )
#        set(DST_PATH "${PROJECT_BINARY_DIR}")
##        message( STATUS "${CMAKE_COMMAND} -E copy ${SRC_PATH} ${DST_PATH}/${FILE_NAME}" )
#        get_filename_component( FILE_NAME ${SRC_PATH} NAME )
##        add_custom_command(TARGET ${PROJECT_NAME}
##                           POST_BUILD
##                           COMMAND ${CMAKE_COMMAND} -E copy ${SRC_PATH} ${DST_PATH}/${FILE_NAME}
##                           COMMENT "Copying shared object ${SRC_PATH} to ${DST_PATH}" )
#    endforeach()
#endmacro()
