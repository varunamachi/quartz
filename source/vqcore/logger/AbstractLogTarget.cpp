
#include <QString>

#include "ILogFormatter.h"
#include "LogUtil.h"
#include "AbstractLogTarget.h"


namespace Vam { namespace Logger {


class AbstractLogTarget::Impl
{
public:
    inline explicit Impl( const QString &uniqueId )
        : m_uniqueId( uniqueId )
        , m_formatter( nullptr )
    {

    }

    inline const QString & uniqueId() const
    {
        return m_uniqueId;
    }

    inline void setFormatterOwned( ILogFormatter *formatter )
    {
        m_formatter.reset( formatter );
    }

    inline ~Impl() { }

    inline ILogFormatter * formatter() const
    {
        return m_formatter.get();
    }

private:
    const QString m_uniqueId;

    std::unique_ptr< ILogFormatter > m_formatter;

};


AbstractLogTarget::AbstractLogTarget( QString &uniqueId )
    : m_impl( std::make_unique< AbstractLogTarget::Impl >( uniqueId ))
{

}

const QString & AbstractLogTarget::uniqueId() const
{
    return m_impl->uniqueId();
}

void AbstractLogTarget::setFormatterOwned( ILogFormatter *formatter )
{
    m_impl->setFormatterOwned( formatter );
}

void AbstractLogTarget::write( const LogMessage *message )
{
    auto formatter = m_impl->formatter();
    this->write(( formatter != nullptr ) ? ( formatter->format( message ))
                                         : LogUtil::format( message ));
}

AbstractLogTarget::~AbstractLogTarget()
{

}

ILogFormatter * AbstractLogTarget::formatter() const
{
    return m_impl->formatter();
}



} }
