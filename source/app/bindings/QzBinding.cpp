
#include <core/logger/Logging.h>

#include "QzBinding.h"


void Qz::info( QString module, QString msg )
{
    QZ_INFO( module ) << msg;
}

void Qz::error( QString module, QString msg )
{
    QZ_ERROR( module ) << msg;
}

void Qz::statusSuccess( QString msg )
{
    QZ_INFO( "Status" ) << msg;
}

void Qz::statusFailure( QString msg )
{
    QZ_ERROR( "Status" ) << msg;
}
