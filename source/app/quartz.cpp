#include <memory>

#include <QApplication>
#include <QQmlEngine>
#include <QDir>
#include <QFileInfo>
#include <QDebug>


#include <core/logger/Logging.h>
#include <core/logger/SpooledDispatcher.h>
#include <core/logger/ConsoleTarget.h>
#include <core/logger/FileTarget.h>
#include <core/app_config/DefaultStorageStrategy.h>
#include <core/app_config/ConfigManager.h>
#include <core/app_config/XMLConfigLoader.h>

#include <base/QzAppContext.h>

#include "inbuilt/LogView.h"
#include "bindings/QzBinding.h"

#include "QuartzFramelessWindow.h"
//#include "QuartzFramedWindow.h"

bool createFileSystem()
{
    using namespace Quartz;
    bool result = false;
    auto path = QzAppContext::expand( StdPath::DataDirectory );
    QFileInfo info{ path };
    if( ! ( info.exists() && info.isDir() )) {
        QDir dir{ "" };
        result = dir.mkpath( path );
    }
    return result;
}

bool initLogger()
{
    using namespace Quartz;
#ifdef QT_DEBUG
    const auto llevel = Logger::LogLevel::Trace;
#else
    const auto llevel = Logger::LogLevel::Info;
#endif
    std::unique_ptr< Logger::SpooledDispatcher >
            dispatcher{ new Logger::SpooledDispatcher{} };
    auto result = Logger::Logger::init( std::move( dispatcher ), llevel );
    if( result ) {
        std::unique_ptr< Logger::ConsoleTarget > consoleTarget{
            new Logger::ConsoleTarget{} };
        Logger::Logger::get()->dispatcher()->addTarget(
                    std::move( consoleTarget ));
        auto path = QzAppContext::expand( StdPath::LogDirectory );
        std::unique_ptr< Logger::FileTarget > fileTarget{
            new Logger::FileTarget{ path, "quartz" }};


    }
    else {
        qDebug() << "Logger initialization failed";
    }
    return result;
}

std::unique_ptr< Quartz::ConfigManager > initConfigManager()
{
    using namespace Quartz;
    auto storeFunc = []( const QString &key,
                         const QString &domain,
                         const QVariant &val ) {
        QzAppContext::get()->configManager()->store( key, val, domain );
    };
    auto path = QzAppContext::expand( StdPath::DataDirectory ) +
            "/quartz.db";
    std::unique_ptr< DefaultStorageStrategy > storageStrategy{
        new DefaultStorageStrategy{ path }};
    std::unique_ptr< XMLConfigLoader > loader{
        new XMLConfigLoader{ storeFunc }};
    std::unique_ptr< ConfigManager > confMan{
        new ConfigManager{ std::move( storageStrategy ),
                           std::move( loader )}};
    return confMan;
}

bool initApp( Quartz::ConfigManager *configManager )
{
    if( configManager == nullptr ) {
        qDebug() << "Config manager iniaization failed";
        return false;
    }
    using namespace Quartz;
    std::unique_ptr< QzAppContext > context{ new QzAppContext{} };
    context->setLogger( Logger::Logger::get() );
    context->setConfigManager( configManager );
    QzCoreContext::setInstance( std::move( context ));
    qmlRegisterSingletonType< QzBinding >( "qz.app",
                                           1,
                                           0,
                                           "Service",
                                           &QzBinding::qmlInstance );
    return true;
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
    auto result = initLogger();
    auto confMan = initConfigManager();
    result = result && initApp( confMan.get() );
    if( result ) {
        QApplication app( argc, argv );
        Quartz::QuartzFramelessWindow window;
        window.show();
        auto returnCode = app.exec();
        uninit();
        return returnCode;
    }
    else {
        qDebug() << "Application initialization failed";
    }

    return -1;
}

