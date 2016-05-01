#pragma once

#include <QString>

namespace Vam {

template< typename ReturnType >
class Result
{
public:
    Result()
        : m_result( false )
        , m_data()
        , m_reason( tr( "Unknown error!" ))
    {

    }

    Result( Result &&other )
        : m_result( other.result() )
        , m_data( std::move( other.data() ))
        , m_reason( std::move( other.reason() ))
    {

    }

    Result( Result &other )
        : m_result( other.result() )
        , m_data( other.data() )
        , m_reason( other.reason() )
    {

    }

    Result( bool result,
            ReturnType data,
            QString &&reason )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( std::move( reason ))
    {

    }

    Result( bool result,
            ReturnType data,
            const QString &reason )
        : m_result( result )
        , m_data( std::move( data ))
        , m_reason( reason )
    {

    }

    ~Result() { }

    bool operator==( Result &other )
    {
        bool same = this == &other
                || ( other.result() == this->m_result
                     && other.data() == this->m_data
                     && other.reason() == this->m_reason );
        return same;
    }

    Result & operator = ( Result &other )
    {
        if( this != &other ) {
            this->m_data = other.data();
            this->m_result = other.result();
            this->m_reason = other.reason();
        }
        return *this;
    }

    Result & operator = ( Result &&other )
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

    bool operator!() const
    {
        return ! m_result;
    }


    static Result< ReturnType > success( ReturnType data );

    static Result< ReturnType > failure( ReturnType data,
                                         const QString &reason );

    static Result< ReturnType > failure( ReturnType data,
                                         const QString &&reason );

    bool result() const;

    const QString & reason() const;

    ReturnType & data() const;

private:
    bool m_result;

    ReturnType m_data;

    QString m_reason;

};


template< typename ReturnType >
Result< ReturnType > Result< ReturnType >::success( ReturnType data )
{
    return Result< ReturnType >( true, data, "" );
}


template< typename ReturnType >
Result< ReturnType > Result< ReturnType >::failure( ReturnType data,
                                                    const QString &reason)
{
    return Result< ReturnType >( false, data, reason );
}


template< typename ReturnType >
bool Result< ReturnType >::result() const
{
    return m_result;
}


template< typename ReturnType >
ReturnType & Result< ReturnType >::data() const
{
    return m_data;
}


template< typename ReturnType >
const QString & Result< ReturnType >::reason() const
{
    return m_reason;
}



//----- Specialization for bool
template<>
class Result< bool >
{
public:
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
            QString &&reason )
        : m_result( result )
        , m_reason( std::move( reason ))
    {

    }

    Result( bool result,
            const QString &reason )
        : m_result( result )
        , m_reason( reason )
    {

    }

    ~Result() { }

    bool operator==( Result &other )
    {
        bool same = this == &other
                || ( other.result() == this->m_result
                     && other.reason() == this->m_reason );
        return same;
    }

    Result & operator = ( Result &other )
    {
        if( this != &other ) {
            this->m_result = other.result();
            this->m_reason = other.reason();
        }
        return *this;
    }

    Result & operator = ( Result &&other )
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



    static Result< bool > success();

    static Result< bool > failure( const QString &reason );

    static Result< bool > failure( const QString &&reason );

    bool result() const;

    const QString & reason() const;

    bool & data() const;

private:
    bool m_result;

    QString m_reason;

};


template<>
Result< bool > Result< bool >::success()
{
    return Result< bool >( true, "" );
}


template<>
Result< bool > Result< bool >::failure( const QString &reason )
{
    return Result< bool >( false, reason );
}


template<>
bool Result< bool >::result() const
{
    return m_result;
}


template<>
bool & Result< bool >::data() const
{
    return m_result;
}


template<>
const QString & Result< bool >::reason() const
{
    return m_reason
}



}
