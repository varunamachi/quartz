
#include <QTextStream>

#include <core/logger/LogUtil.h>
#include <core/logger/ILogFormatter.h>
#include <core/logger/LogMessage.h>
#include <core/logger/LogStructures.h>

#include "LogView.h"

namespace Quartz {


struct LogView::Data
{

};

void LogView::flush()
{

}

void LogView::write( const Logger::LogMessage *message )
{
    using namespace Logger;
    //put only whats required into a model
}

void LogView::write( QString &&/*logString*/ )
{

}




}
