message( STATUS "------- Container: ${CMAKE_PROJECT_NAME} | "
                "Project: ${PROJECT_NAME} -------" )

set( VQ_PROJECT_DEFINED ON )

if( DEFINED VQ_IS_PROJECT_CONTAINER
    AND ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR} )
    message( FATAL_ERROR "Project container cannot be a project" )
endif()


if( ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR} )
    message( FATAL_ERROR "In-source build is not allowed. "
                         "Choose a different build directory"
                         " i.e. Run cmake from somewhere else ")
endif()

if( DEFINED VQ_PROJECT_${PROJECT_NAME}_DEFINED )
    message( FATAL_ERROR "Duplicate project found. Make sure that "
                         "vqcore.cmake is not included in any subdirectory's "
                         "CMakeLists.txt" )
endif()

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU )
#     if( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.9 )
  if( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.8 )
        message( FATAL_ERROR "Insufficient GCC version. Minimum is GCC 4.9" )
    endif()
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC )
    if( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 18 )
        message( FATAL_ERROR "Insufficient MSVC version. Minimum is MSVC 18"
                             " i.e Visual Studio 2013" )
    endif()
endif()

if( UNIX )
    SET( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:$ORIGIN" )
endif()

set( CMAKE_INSTALL_PREFIX ${VQ_OUTPUT_DIR} )
set( VQ_PROJECT_DEFINED ON )
set( "VQ_PROJECT_${PROJECT_NAME}_DEFINED" ON )
set( VQ_LIB_EXT ".a" )
set( VQ_SO_EXT ".so")
set( VQ_LIB_PREFIX "lib" )

#Now GCC Specific
if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

#MSVC Specific
if( ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC )
    set( VQ_LIB_EXT ".lib" )
    set( VQ_SO_EXT ".dll")
    set( VQ_LIB_PREFIX "" )
    add_definitions( -DWIN32_LEAN_AND_MEAN )
    add_definitions( -D_SCL_SECURE_NO_WARNINGS )
    add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

set( CMAKE_DEBUG_POSTFIX "d" )
set( CMAKE_VERBOSE_MAKEFILE ON )


set( VQ_INCLUDE_DIRS   "" )
set( VQ_LINK_DIRS      "" )
set( VQ_LIBS_DEBUG     "" )
set( VQ_LIBS_RELEASE   "" )
set( VQ_DEPENDENCIES   "" )


macro( vq_set_prop KEY VALUE )
    set_property( GLOBAL PROPERTY ${KEY} ${VALUE} )
endmacro( vq_set_prop )


macro( vq_get_prop VALUE KEY )
    get_property( ${VALUE} GLOBAL PROPERTY "${KEY}" )
endmacro( vq_get_prop )


if( DEFINED VQ_IS_PROJECT_CONTAINER )
    get_filename_component( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH )
    vq_set_prop( BIN_DIR_${PROJECT_NAME}  ${CMAKE_CURRENT_BINARY_DIR} )
    vq_set_prop( INCLUDE_DIR_${PROJECT_NAME} ${INCLUDE_DIR} )
    vq_set_prop( ${PROJECT_NAME}_SUBPROJECT ON )
endif( DEFINED VQ_IS_PROJECT_CONTAINER )


macro( vq_add_qt )
    set( CMAKE_AUTOMOC ON )
    set( CMAKE_AUTOUIC ON )
    set( CMAKE_INCLUDE_CURRENT_DIR ON )
    find_package( Qt5Widgets )
    list( APPEND VQ_INCLUDE_DIRS ${Qt5Widgets_INCLUDE_DIRS} )
    list( APPEND VQ_LIBS_DEBUG Qt5::Widgets )
    list( APPEND VQ_LIBS_RELEASE Qt5::Widgets )
endmacro( vq_add_qt )


function( vq_internal_module REL_INCL_PATH MODULE_NAME )
    get_property( MODULE_TYPE TARGET ${MODULE_NAME} PROPERTY TYPE )
    message( STATUS "In Source Include: ${MODULE_NAME}" )
    vq_get_prop( MDL_INCL_DIR INCLUDE_DIR_${MODULE_NAME} )
    vq_get_prop( MDL_BUILD_PATH BIN_DIR_${MODULE_NAME} )
    set( VQ_INCLUDE_DIRS ${VQ_INCLUDE_DIRS} ${MDL_INCL_DIR} PARENT_SCOPE )
    set( VQ_LINK_DIRS ${VQ_LINK_DIRS} ${MDL_BUILD_PATH} PARENT_SCOPE )
    set( VQ_BIN_DIR ${VQ_BIN_DIR} ${MDL_BUILD_PATH} PARENT_SCOPE )
    set( VQ_DEPENDENCIES ${VQ_DEPENDENCIES} ${MODULE_NAME} PARENT_SCOPE )

    set( LIB_STR ${MDL_BUILD_PATH}/${VQ_LIB_PREFIX}${MODULE_NAME} )
    set( DEBUG_LIB ${LIB_STR}d${VQ_LIB_EXT} )
    set( RELEASE_LIB ${LIB_STR}${VQ_LIB_EXT} )
    if( UNIX AND ( MODULE_TYPE STREQUAL "SHARED_LIBRARY" ))
        set( DEBUG_LIB ${LIB_STR}d${VQ_SO_EXT} )
        set( RELEASE_LIB ${LIB_STR}${VQ_SO_EXT} )
    endif()
    set( VQ_LIBS_DEBUG  ${VQ_LIBS_DEBUG} ${DEBUG_LIB} PARENT_SCOPE )
    set( VQ_LIBS_RELEASE ${VQ_LIBS_RELEASE} ${RELEASE_LIB} PARENT_SCOPE )
endfunction()


function( vq_deployed_module REL_INCL_PATH MODULE_NAME )
    message( STATUS "Out Source Include: ${MODULE_NAME}" )
    set( ABS_INCL_DIR ${VQ_OUTPUT_DIR}/include/${REL_INCL_PATH} )
    set( VQ_INCLUDE_DIRS ${VQ_INCLUDE_DIRS} ${ABS_INCL_DIR} PARENT_SCOPE )
    set( VQ_LINK_DIRS ${VQ_LINK_DIRS} ${VQ_OUTPUT_DIR}/lib PARENT_SCOPE )
    set( VQ_BIN_DIRS ${VQ_BIN_DIRS} ${VQ_OUTPUT_DIR}/bin PARENT_SCOPE )

    set( STATIC_LIB_STR ${VQ_OUTPUT_DIR}/lib/${VQ_LIB_PREFIX}${MODULE_NAME} )
    set( DEBUG_STATIC ${STATIC_LIB_STR}d${VQ_LIB_EXT} )
    set( RELEASE_STATIC ${STATIC_LIB_STR}${VQ_LIB_EXT} )

    set( SHARED_LIB_STR ${VQ_OUTPUT_DIR}/bin/${VQ_LIB_PREFIX}${MODULE_NAME} )
    set( DEBUG_SO ${SHARED_LIB_STR}d${VQ_LIB_EXT} )
    set( RELEASE_SO ${SHARED_LIB_STR}${VQ_LIB_EXT} )

    if( UNIX AND ( EXISTS ${DEBUG_SO} OR EXISTS ${RELEASE_SO} ))
        set( VQ_LIBS_DEBUG  ${VQ_LIBS_DEBUG} ${DEBUG_SO} PARENT_SCOPE )
        set( VQ_LIBS_RELEASE ${VQ_LIBS_RELEASE} ${RELEASE_SO} PARENT_SCOPE )
    else()
        set( VQ_LIBS_DEBUG  ${VQ_LIBS_DEBUG} ${DEBUG_STATIC} PARENT_SCOPE )
        set( VQ_LIBS_RELEASE ${VQ_LIBS_RELEASE} ${RELEASE_STATIC} PARENT_SCOPE )
    endif()
endfunction()


macro( vq_add_module REL_INCL_PATH MODULE_NAME )
    get_property( IS_SUBPROJECT GLOBAL PROPERTY ${MODULE_NAME}_SUBPROJECT )
    if( IS_SUBPROJECT )
        vq_internal_module( ${REL_INCL_PATH} ${MODULE_NAME} )
    else()
        vq_deployed_module( ${REL_INCL_PATH} ${MODULE_NAME} )
    endif()
endmacro()


macro( vq_sources )
    foreach( SRC_FILE ${ARGV} )
        set( FULL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE} )
        set_property( GLOBAL APPEND PROPERTY ${PROJECT_NAME}_SRC "${FULL_SRC}" )
    endforeach()
endmacro( vq_sources )


macro( vq_headers  )
    foreach( HDR_FILE ${ARGV} )
        set( FULL_HDR ${CMAKE_CURRENT_SOURCE_DIR}/${HDR_FILE} )
        set_property( GLOBAL APPEND PROPERTY ${PROJECT_NAME}_HDR "${FULL_HDR}" )
    endforeach()
endmacro( vq_headers )


macro( vq_classes )
    foreach( SRC_FILE ${ARGV} )
        vq_headers( ${SRC_FILE}.h )
        set( SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}.cpp )
        if( EXISTS "${SOURCE}" )
            vq_sources( ${SRC_FILE}.cpp )
        endif()
    endforeach()
endmacro( vq_classes )


macro( vq_interfaces )
    foreach( SRC_FILE ${ARGV} )
        vq_headers( ${SRC_FILE}.h )
    endforeach()
endmacro( vq_interfaces )




macro( pre_add_bin )
    if( UNIX )
        set( VQ_LIBS_DEBUG ${VQ_LIBS_DEBUG} dl )
        set( VQ_LIBS_RELEASE ${VQ_LIBS_RELEASE} dl )
    endif()
    include_directories( ${VQ_INCLUDE_DIRS} )
    link_directories( ${VQ_LINK_DIRS} )
#    vq_print_dirs()
endmacro()


macro( post_add_bin )
    if( ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_DEPRECATE" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_NONSTDC_NO_DEPRECATE" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNICODE" )
        set( VQ_LIBS_DEBUG ${VQ_LIBS_DEBUG} ws2_32 setupapi )
        set( VQ_LIBS_RELEASE ${VQ_LIBS_RELEASE} ws2_32 setupapi )
    endif()
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        if( VQ_LIBS_DEBUG )
            message( STATUS "Libs Build Type: DEBUG" )
            set( DEBUG_LIB_DUP ${VQ_LIBS_DEBUG} ${VQ_LIBS_DEBUG} )
            list( REMOVE_ITEM DEBUG_LIB_DUP "debug" )
            target_link_libraries( ${PROJECT_NAME} debug ${DEBUG_LIB_DUP} )
        endif( VQ_LIBS_DEBUG )
    else()
        if( VQ_LIBS_RELEASE )
            message( STATUS "Libs Build Type: Release" )
            set( RELEASE_LIB_DUP ${VQ_LIBS_RELEASE} ${VQ_LIBS_RELEASE} )
            list( REMOVE_ITEM RELEASE_LIB_DUP "optimized" )
            target_link_libraries( ${PROJECT_NAME} optimized ${RELEASE_LIB_DUP})
        endif( VQ_LIBS_RELEASE )
    endif()
    if( UNIX )
        SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
    endif( )
    list( LENGTH VQ_DEPENDENCIES NUM_DEP )
    if( VQ_DEPENDENCIES )
        add_dependencies( ${PROJECT_NAME} ${VQ_DEPENDENCIES} )
    endif()
endmacro()


macro( vq_create_staticlib )
    include_directories( ${VQ_INCLUDE_DIRS} )
    get_property( VQ_SRC_LIST GLOBAL PROPERTY ${PROJECT_NAME}_SRC )
    get_property( VQ_HDR_LIST GLOBAL PROPERTY ${PROJECT_NAME}_HDR )
    add_library( ${PROJECT_NAME} ${VQ_SRC_LIST} ${VQ_HDR_LIST} )
    if( NOT ${ARGV0}  STREQUAL "" )
        set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${ARGV0} )
    endif()
#    vq_print_dirs()
endmacro( vq_create_staticlib )


macro( vq_create_sharedlib )
    pre_add_bin()
    get_property( VQ_SRC_LIST GLOBAL PROPERTY ${PROJECT_NAME}_SRC )
    get_property( VQ_HDR_LIST GLOBAL PROPERTY ${PROJECT_NAME}_HDR )
    add_library( ${PROJECT_NAME} SHARED ${VQ_SRC_LIST} ${VQ_HDR_LIST} )
    if( NOT ${ARGV0}  STREQUAL "" )
        set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${ARGV0} )
    endif()
    post_add_bin()
endmacro()


macro( vq_create_app )
    pre_add_bin()
    get_property( VQ_SRC_LIST GLOBAL PROPERTY ${PROJECT_NAME}_SRC )
    get_property( VQ_HDR_LIST GLOBAL PROPERTY ${PROJECT_NAME}_HDR )
    if( WIN32 )
        add_executable( ${PROJECT_NAME} WIN32 ${VQ_SRC_LIST} ${VQ_HDR_LIST} )
    else()
        add_executable( ${PROJECT_NAME} ${VQ_SRC_LIST} ${VQ_HDR_LIST} )
    endif()
    if( NOT ${ARGV0}  STREQUAL "" )
        set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${ARGV0} )
    endif()
    post_add_bin()
endmacro()


macro( vq_install_plugin )
    install( TARGETS ${PROJECT_NAME} DESTINATION Bin/plugins )
endmacro( vq_install_plugin )

macro( vq_install_headers )
    get_property( VQ_HDR_LIST GLOBAL PROPERTY ${PROJECT_NAME}_HDR )
    foreach( HEADER ${VQ_HDR_LIST} )
        file( RELATIVE_PATH REL_PATH ${VQ_SRC_DIR} ${HEADER} )
        get_filename_component( DIR ${REL_PATH} DIRECTORY )
        install( FILES ${HEADER} DESTINATION "include/${DIR}" )
    endforeach()
endmacro( vq_install_headers DEST )


macro( vq_install )
    get_property( MODULE_TYPE TARGET ${PROJECT_NAME} PROPERTY TYPE )
    if( MODULE_TYPE STREQUAL "STATIC_LIBRARY" )
        vq_install_headers()
        install( TARGETS ${PROJECT_NAME} DESTINATION lib )
    elseif( MODULE_TYPE STREQUAL "SHARED_LIBRARY" )
        vq_install_headers()
        install( TARGETS ${PROJECT_NAME}
            LIBRARY DESTINATION "lib"
            ARCHIVE DESTINATION "lib"
            RUNTIME DESTINATION "bin"
            BUNDLE DESTINATION "bin"
            FRAMEWORK DESTINATION "bin" )
    elseif( MODULE_TYPE STREQUAL "EXECUTABLE" )
        install( TARGETS ${PROJECT_NAME} DESTINATION bin )
        if( WIN32 )
            install_qt5_executable( "bin/${PROJECT_NAME}.exe" )
        else()
            install_qt5_executable( "bin/${PROJECT_NAME}" )
        endif()
    else()
        message( FATAL "Install failed: unrecognized target type" )
    endif()
endmacro()



function( vq_dump_vars )
    message( STATUS "---------- Dirs ${PROJECT_NAME} ---------------" )
    foreach( INCL_DIR ${VQ_INCLUDE_DIRS} )
        message( STATUS ">> INCLUDE: ${INCL_DIR}" )
    endforeach()
    foreach( LINK_DIR ${VQ_LINK_DIRS} )
        message( STATUS "*** LINK: ${LINK_DIR}" )
    endforeach()
    foreach( DLIB ${VQ_LIBS_DEBUG} )
        message( STATUS "*** DEBUG: ${DLIB}" )
    endforeach()
    foreach( RLIB ${VQ_LIBS_RELEASE} )
        message( STATUS "*** RELEASE: ${RLIB}" )
    endforeach()
    message( STATUS "XXXXXXXXXX Dirs ${PROJECT_NAME} XXXXXXXXXXXXXXX" )
endfunction()



#function( vq_add_module REL_INCL_PATH MODULE_NAME )
#    get_property( IS_SUBPROJECT GLOBAL PROPERTY ${MODULE_NAME}_SUBPROJECT )
#    if( IS_SUBPROJECT )
#        message( STATUS "In Source Include: ${MODULE_NAME}" )
#        vq_get_prop( MDL_INCL_DIR INCLUDE_DIR_${MODULE_NAME} )
#        vq_get_prop( MDL_BUILD_PATH BIN_DIR_${MODULE_NAME} )
#        set( VQ_INCLUDE_DIRS ${VQ_INCLUDE_DIRS} ${MDL_INCL_DIR} PARENT_SCOPE )
#        set( VQ_LINK_DIRS ${VQ_LINK_DIRS} ${MDL_BUILD_PATH} PARENT_SCOPE )
#        set( VQ_BIN_DIR ${VQ_BIN_DIR} ${MDL_BUILD_PATH} PARENT_SCOPE )
#        set( VQ_DEPENDENCIES ${VQ_DEPENDENCIES} ${MODULE_NAME} PARENT_SCOPE )
#    else()
#        set( ABS_INCL_DIR ${VQ_OUTPUT_DIR}/include/${REL_INCL_PATH} )
#        set( VQ_INCLUDE_DIRS ${VQ_INCLUDE_DIRS} ${ABS_INCL_DIR} PARENT_SCOPE )
#        set( VQ_LINK_DIRS ${VQ_LINK_DIRS} ${VQ_OUTPUT_DIR}/lib PARENT_SCOPE )
#        set( VQ_BIN_DIRS ${VQ_BIN_DIRS} ${VQ_OUTPUT_DIR}/bin PARENT_SCOPE )
#        message( STATUS "Out Source Include: ${MODULE_NAME}" )
#    endif()
#    set( DEBUG_LIB ${LIB_PREFIX}${MODULE_NAME}d${LIB_EXT} )
#    set( RELEASE_LIB ${LIB_PREFIX}${MODULE_NAME}${LIB_EXT} )
#    set( VQ_LIBS_DEBUG  ${VQ_LIBS_DEBUG} ${DEBUG_LIB} PARENT_SCOPE )
#    set( VQ_LIBS_RELEASE ${VQ_LIBS_RELEASE} ${RELEASE_LIB} PARENT_SCOPE )
#endfunction()

#macro( vq_install_lib )
#    install( TARGETS ${PROJECT_NAME} DESTINATION lib )
#endmacro( vq_install_lib )


#macro( vq_install_bin )
#    install( TARGETS ${PROJECT_NAME} DESTINATION bin )
#    if( WIN32 )
#        install_qt5_executable( "bin/${PROJECT_NAME}.exe" )
#    else()
#        install_qt5_executable( "bin/${PROJECT_NAME}" )
#    endif()
#endmacro( vq_install_bin )
