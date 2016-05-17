#pragma once

#define TOKENPASTE( x, y ) x##y
#define TOKENPASTE2( x, y ) TOKENPASTE( x, y )
#define LINE_VAR( n ) TOKENPASTE2( n, __LINE__ )

#define VQ_NO_COPY( ClassName ) \
    ClassName( const ClassName &other ) = delete; \
    ClassName & operator=( const ClassName &other ) = delete \

#define VQ_NO_MOVE( ClassName ) \
    ClassName( ClassName && rval ) = delete; \
    ClassName & operator=( const ClassName &&rval ) = delete \

#define VQ_NO_COPY_OR_MOVE( ClassName ) \
    VQ_NO_COPY( ClassName ); \
    VQ_NO_MOVE( ClassName )

#define VQ_MAKE_STATIC( ClassName ) \
    ClassName() = delete; \
    ~ClassName() = delete; \
    bool operator == ( const ClassName &other ) = delete; \
    VQ_NO_COPY_OR_MOVE( ClassName )



