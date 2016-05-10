
#include "Result.h"


namespace Vam {

Result< bool > Result< bool >::success()
{
    return Result< bool >( true, "" );
}


Result< bool > Result< bool >::failure( const QString &reason )
{
    return Result< bool >( false, reason );
}


Result< bool > Result< bool >::failure( const QString &&reason )
{
    return Result< bool >( false, std::move( reason ));
}


bool Result< bool >::result() const
{
    return m_result;
}



bool & Result< bool >::data()
{
    return m_result;
}


const QString & Result< bool >::reason() const
{
    return m_reason;
}


}
