#pragma once

#define QZ_INTERFACE struct
#define QZ_SCOPE( _zed )

#define QZ_OUT
#define QZ_IN_OUT

#define TOKENPASTE( x, y ) x##y
#define TOKENPASTE2( x, y ) TOKENPASTE( x, y )
#define LINE_VAR( n ) TOKENPASTE2( n, __LINE__ )

#define QZ_NO_COPY( ClassName ) \
    ClassName( const ClassName &other ) = delete; \
    ClassName & operator=( const ClassName &other ) = delete \

#define QZ_NO_MOVE( ClassName ) \
    ClassName( ClassName && rval ) = delete; \
    ClassName & operator=( const ClassName &&rval ) = delete \

#define QZ_NO_COPY_OR_MOVE( ClassName ) \
    QZ_NO_COPY( ClassName ); \
    QZ_NO_MOVE( ClassName )

#define QZ_MAKE_STATIC( ClassName ) \
    ClassName() = delete; \
    ~ClassName() = delete; \
    bool operator == ( const ClassName &other ) = delete; \
    QZ_NO_COPY_OR_MOVE( ClassName )



