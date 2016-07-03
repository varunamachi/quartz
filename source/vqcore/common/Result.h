#pragma once

#include <string>

namespace Vq {

template< typename ReturnType >
class Result
{
public:
    Result()
        : m_result( false )
        , m_data()
        , m_reason( "Unknown error!" )
    {

    }

    Result( Result< ReturnType > &&other )
        : m_result( other.result() )
        , m_data( std::move( other.data() ))
        , m_reason( std::move( other.reason() ))
    {

    }

    Result( const Result< ReturnType > &other )
        : m_result( other.result() )
        , m_data( other.data() )
        , m_reason( other.reason() )
    {

    }

    Result( bool result,
            ReturnType data,
            std::string &&reason )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( std::move( reason ))
    {

    }

    Result( bool result,
            ReturnType data,
            const std::string &reason )
        : m_result( result )
        , m_data( data )
        , m_reason( reason )
    {

    }

    Result( bool result,
            ReturnType &&data,
            const std::string &reason )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( reason )
    {

    }

    Result( bool result,
            ReturnType &&data,
            const std::string &&reason )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( std::move( reason ))
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

    static Result< ReturnType > success( const ReturnType &data );

    static Result< ReturnType > success( ReturnType &&data );

    static Result< ReturnType > failure( ReturnType data,
                                         const std::string &reason );

    static Result< ReturnType > failure( ReturnType data,
                                         std::string &&reason );

    bool result() const;

    const std::string & reason() const;

    ReturnType & data();

private:
    bool m_result;

    ReturnType m_data;

    std::string m_reason;

//    int m_errorCode;
};


template< typename ReturnType >
Result< ReturnType > Result< ReturnType >::success( const ReturnType &data )
{
    return Result< ReturnType >( true, data, "" );
}


template< typename ReturnType >
Result< ReturnType > Result< ReturnType >::success( ReturnType &&data )
{
    return Result< ReturnType >( true, std::move( data ), "" );
}


template< typename ReturnType >
Result< ReturnType > Result< ReturnType >::failure( ReturnType data,
                                                    const std::string &reason )
{
    return Result< ReturnType >( false, data, reason );
}


template< typename ReturnType >
Result< ReturnType > Result< ReturnType >::failure( ReturnType data,
                                                    std::string &&reason )
{
    return Result< ReturnType >( false, data, std::move( reason ));
}


template< typename ReturnType >
bool Result< ReturnType >::result() const
{
    return m_result;
}


template< typename ReturnType >
ReturnType & Result< ReturnType >::data()
{
    return m_data;
}


template< typename ReturnType >
const std::string & Result< ReturnType >::reason() const
{
    return m_reason;
}



//----- Specialization for bool
template<>
class Result< bool >
{
public:
    Result()
        : m_result( false )
        , m_reason( "" )
    {

    }

    Result( Result &&other )
        : m_result( other.result() )
        , m_reason( std::move( other.reason() ))
    {

    }

    Result( Result &other )
        : m_result( other.result() )
        , m_reason( other.reason() )
    {

    }

    Result( bool result,
            std::string &&reason )
        : m_result( result )
        , m_reason( std::move( reason ))
    {

    }

    Result( bool result,
            const std::string &reason )
        : m_result( result )
        , m_reason( reason )
    {

    }

    ~Result() { }

    bool operator==( const Result< bool > &other )
    {
        bool same = this == &other
                || ( other.result() == this->m_result
                     && other.reason() == this->m_reason );
        return same;
    }

    Result & operator = ( const Result< bool > &other )
    {
        if( this != &other ) {
            this->m_result = other.result();
            this->m_reason = other.reason();
        }
        return *this;
    }

    Result & operator = ( Result< bool > &&other )
    {
        if( this != &other ) {
            this->m_result = other.result();
            this->m_reason = std::move( other.reason() );
        }
        return *this;
    }

    explicit operator bool() const
    {
        return m_result;
    }

    static Result< bool > success()
    {
        return Result< bool >( true, "" );
    }


    static Result< bool > failure( const std::string &reason )
    {
        return Result< bool >( false, reason );
    }


    static Result< bool > failure( const std::string &&reason )
    {
        return Result< bool >( false, std::move( reason ));
    }


    bool result() const
    {
        return m_result;
    }



    bool & data()
    {
        return m_result;
    }


    const std::string & reason() const
    {
        return m_reason;
    }

private:
    bool m_result;

    std::string m_reason;

};


}
