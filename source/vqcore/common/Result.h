#pragma once

#include <QString>

namespace Vam {

template< typename ReturnType >
class Result
{
public:
    Result( Result &&other )
        : m_result( other.result() )
        , m_data( std::move( other.data() ))
        , m_reason( std::move( other.reason() ))
    {

    }

    static void success( ReturnType data );

    static void failure( ReturnType data, const QString &reason );

    static void failure( ReturnType data, const QString &&reason );

    bool result() const;

    const QString & reason() const;

    ReturnType data() const;

private:
    bool m_result;

    ReturnType m_data;

    QString m_reason;

};
}
