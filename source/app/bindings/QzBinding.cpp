
#include <core/logger/Logging.h>

#include "QzBinding.h"


void Qz::info(QString msg)
{
    QZ_INFO( "QML" ) << msg;
}

void Qz::statusSuccess(QString msg)
{

}

void Qz::statusFailure(QString msg)
{

}
