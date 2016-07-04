#pragma once

#include <string>

namespace Vq {

using ErrorCodeType = std::int64_t;

#define VQ_TO_ERR( code ) static_cast< ErrorCodeType >(( code ))

template< typename ReturnType >
class Result
{
public:

    Result()
        : m_result( false )
        , m_data()
        , m_reason( "Unknown error!" )
        , m_errorCode( 0 )
    {

    }

    Result( Result< ReturnType > &&other )
        : m_result( other.result() )
        , m_data( std::move( other.data() ))
        , m_reason( std::move( other.reason() ))
        , m_errorCode( std::move( other.errorCode() ))
    {

    }

    Result( const Result< ReturnType > &other )
        : m_result( other.result() )
        , m_data( other.data() )
        , m_reason( other.reason() )
        , m_errorCode( other.erroCode() )
    {

    }

    Result( bool result,
            ReturnType data,
            std::string &&reason,
            ErrorCodeType errorCode )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( std::move( reason ))
        , m_errorCode( errorCode )
    {

    }

    Result( bool result,
            ReturnType data,
            const std::string &reason,
            ErrorCodeType errorCode )
        : m_result( result )
        , m_data( data )
        , m_reason( reason )
        , m_errorCode( errorCode )
    {

    }

    Result( bool result,
            ReturnType &&data,
            const std::string &reason,
            ErrorCodeType errorCode )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( reason )
        , m_errorCode( errorCode )
    {

    }

    Result( bool result,
            ReturnType &&data,
            const std::string &&reason,
            ErrorCodeType errorCode )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( std::move( reason ))
        , m_errorCode( errorCode )
    {

    }

    ~Result() { }

    bool operator==( const Result< ReturnType > &other )
    {
        bool same = this == &other
                || ( other.result() == this->m_result
                     && other.data() == this->m_data
                     && other.reason() == this->m_reason );
        return same;
    }

    bool operator==( const ReturnType &other )
    {
        bool same = this->result == other.result;
        return same;
    }

    Result & operator = ( const Result< ReturnType > &other )
    {
        if( this != &other ) {
            this->m_data = other.data();
            this->m_result = other.result();
            this->m_reason = other.reason();
        }
        return *this;
    }

    Result & operator = ( Result< ReturnType > &&other )
    {
        if( this != &other ) {
            this->m_data = std::move( other.data() );
            this->m_result = other.result();
            this->m_reason = std::move( other.reason() );
        }
        return *this;
    }

    explicit operator bool() const
    {
        return m_result;
    }

    bool operator ! () const
    {
        return ! m_result;
    }

    bool result() const
    {
        return m_result;
    }

    const std::string & reason() const
    {
        return m_reason;
    }

    ReturnType & data()
    {
        return m_data;
    }

    ErrorCodeType errorCode() const
    {
        return m_errorCode;
    }

    static Result< ReturnType > success( const ReturnType &data )
    {
        return Result< ReturnType >( true, data, "", 0 );
    }

    static Result< ReturnType > success( ReturnType &&data )
    {
        return Result< ReturnType >( true, std::move( data ), "",  0 );
    }

    static Result< ReturnType > failure( ReturnType data = ReturnType{ },
                                         const std::string &reason = "",
                                         ErrorCodeType errorCode = 0 )
    {
        return Result< ReturnType >( false,
                                     data,
                                     std::move( reason ),
                                     errorCode );
    }

    static Result< ReturnType > failure( ReturnType data,
                                         std::string &&reason,
                                         ErrorCodeType errorCode = 0 )
    {
        return Result< ReturnType >( false,
                                     data,
                                     std::move( reason ),
                                     errorCode );
    }

    static Result< ReturnType > failure( ReturnType data,
                                         ErrorCodeType errorCode = 0 )
    {
        return Result< ReturnType >( false,
                                     data,
                                     "",
                                     errorCode );
    }

private:
    bool m_result;

    ReturnType m_data;

    std::string m_reason;

    ErrorCodeType m_errorCode;
};


}


