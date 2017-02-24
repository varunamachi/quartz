#include <QApplication>
#include <QQmlEngine>

#include <core/logger/Logging.h>
#include <core/logger/SpooledDispatcher.h>
#include <core/logger/ConsoleTarget.h>

#include <base/QzAppContext.h>

#include "inbuilt/LogView.h"
#include "bindings/QzBinding.h"

#include "QuartzFramelessWindow.h"
//#include "QuartzFramedWindow.h"

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

        std::unique_ptr< QzAppContext > context{ new QzAppContext{} };
        context->setLogger( Logger::Logger::get() );
        QzCoreContext::setInstance( std::move( context ));

        qmlRegisterSingletonType< QzBinding >( "qz.app",
                                        1,
                                        0,
                                        "Service",
                                        &QzBinding::qmlInstance );
    }
    return result;
}

bool uninit()
{
    QZ_LOGGER()->dispatcher()->removeTarget( Quartz::LogView::LOG_TARGET_ID );
    QZ_LOGGER()->dispatcher()->stopDispatch();
    QZ_LOGGER()->destroy();
    return true;
}

int main( int argc, char **argv )
{
    init();
    QApplication app( argc, argv );
    Quartz::QuartzFramelessWindow window;
    window.show();
    auto returnCode = app.exec();
    uninit();
    return returnCode;
}

