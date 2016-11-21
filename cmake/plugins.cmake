
macro( create_plugin )
    vq_create_sharedlib()
    set_property( GLOBAL APPEND PROPERTY "PLUGINS"  ${PROJECT_NAME} )
endmacro()
