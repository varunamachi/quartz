#include <QApplication>

#include <core/logger/Logging.h>
#include <core/logger/SpooledDispatcher.h>
#include <core/logger/ConsoleTarget.h>
//#include <core/logger/FileTarget.h>

#include "QuartzWindow.h"



bool init()
{
    using namespace Quartz;
    std::unique_ptr< Logger::SpooledDispatcher > dispatcher{
        new Logger::SpooledDispatcher{} };
    bool result = Logger::Logger::init( std::move( dispatcher ),
                                        Logger::LogLevel::Debug );
    if( result ) {
        std::unique_ptr< Logger::ConsoleTarget > consoleTarget{
            new Logger::ConsoleTarget{} };
        Logger::Logger::get()->dispatcher()->addTarget(
                    std::move( consoleTarget ));
    }
    return result;
}

bool uninit()
{
    QZ_LOGGER()->dispatcher()->stopDispatch();
    QZ_LOGGER()->destroy();
    return true;
}

int main( int argc, char **argv )
{
    init();
    QApplication app( argc, argv );
    Quartz::QuartzWindow window;
    window.show();
    auto returnCode = app.exec();
    uninit();
    return returnCode;
}

