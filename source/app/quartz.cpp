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

#include <common/iconstore/IconFontStore.h>

#include <base/QzAppContext.h>

#include "inbuilt/LogView.h"
#include "bindings/QzBinding.h"

#include "QuartzFramelessWindow.h"
#include "QuartzFramedWindow.h"


QByteArray readAll(QString path) {
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        return file.readAll();
    }
    return QByteArray();
}

void installAppIcon() {
    auto home = QDir::homePath();
    auto iconPath= home + "/.local/share/icons/quartz.png";
    auto configPath = home + "/.local/share/applications/quartz.desktop";
    auto icon = readAll("://resources/quartz.png");
    auto config = readAll("://resources/quartz.desktop");
    QFileInfo iconInfo(iconPath);
    if (!iconInfo.exists() || iconInfo.size() != icon.size()) {
        QFile iFile(iconPath);
        if (!icon.isNull() && iFile.open(QFile::WriteOnly | QFile::Text)) {
            iFile.write(icon);
        } else {
            QZ_ERROR("App") << "Failed to create icon file";
        }
    } else {
        QZ_DEBUG("App") << "No need to install icon";
    }
    QFileInfo configInfo(configPath);
    if (!configInfo.exists() || configInfo.size() != config.size()) {
        QFile cFile(configPath);
        if (!config.isNull() && cFile.open(QFile::WriteOnly | QFile::Text)) {
            cFile.write(config);
        } else {
            QZ_ERROR("App") << "Failed to create desktop file";
        }
    } else {
        QZ_DEBUG("App") << "No need to install desktop file";
    }
}

bool createFileSystem()
{
    using namespace Quartz;
    bool result = true;
    auto path = QzAppContext::expand( StdPath::LogDirectory );
    QFileInfo info{ path };
    if( ! ( info.exists() && info.isDir() )) {
        QDir dir{ "" };
        result = dir.mkpath( path );
    }
    if( ! result ) {
        qDebug() << "Failed to create Quartz file system";
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
        auto path = QzAppContext::expand( StdPath::LogDirectory );
        std::unique_ptr< Logger::FileTarget > fileTarget{
            new Logger::FileTarget{ path, "quartz" }};
        Logger::Logger::get()->dispatcher()->addTarget(
                    std::move( fileTarget ));
        //We need below messages only on log file to distinguish between
        //launches, hence these are logged before console logger is registered
        QZ_INFO( "Qz:App" ) << "---------------------------------------------";
        QZ_INFO( "Qz:App" ) << "Starting Quartz!!!!";
        Logger::Logger::get()->dispatcher()->flush();
        Logger::Logger::get()->dispatcher()->addTarget(
                    std::move( consoleTarget ));

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
    auto path = QzAppContext::expand( StdPath::DataDirectory ) + "/quartz.db";
    std::unique_ptr< DefaultStorageStrategy > storageStrategy{
        new DefaultStorageStrategy{ path }};
    std::unique_ptr< XMLConfigLoader > loader{
        new XMLConfigLoader{ storeFunc }};
    std::unique_ptr< ConfigManager > confMan{
        new ConfigManager{ std::move( storageStrategy ),
                           std::move( loader )}};
    return confMan;
}

bool initApp()
{
    using namespace Quartz;
    std::unique_ptr< QzAppContext > context{ new QzAppContext{} };
    context->setLogger( Logger::Logger::get() );
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
    QZ_LOGGER()->dispatcher()->stopDispatch();
    QZ_LOGGER()->destroy();
    return true;
}

void loadFonts() {
    QByteArrayList fonts;
    QFile files[] = {
        {"://resources/MaterialIconsRegular.ttf"},
        {"://resources/FABrands.ttf"},
        {"://resources/FASolid.ttf"},
//        {"://resources/FARegular.ttf"}
    };
    for (auto &f : files) {
        if (f.exists() && f.open(QFile::ReadOnly)) {
            auto ba = f.readAll();
            if (!ba.isNull()) {
                fonts.append(ba);
            } else {
                QZ_ERROR("App") << f.fileName() << " is empty";
            }
            f.close();
        } else {
            QZ_ERROR("App") << "Failed to open: " << f.fileName();
        }
    }
    Quartz::IconFontStore::init(fonts);
}

int main( int argc, char **argv )
{
    auto returnCode = -1;
    Q_INIT_RESOURCE(quartz);
    auto result = createFileSystem()
            && initLogger()
            && initApp( );
    if( result ) {
        using namespace Quartz;
        auto confMan = initConfigManager();
        context< QzAppContext >()->setConfigManager( confMan.get() );
        QZ_SCOPE( "Make sure that QzMainWidget destroyed before uninit" ) {
            QApplication app( argc, argv );
            loadFonts();
#ifdef Q_OS_LINUX
            installAppIcon();
#endif
            Quartz::QuartzFramedWindow window;
            app.setStyleSheet("QWidget{"
                              " border: solid 1px red;"
                              "}");
            window.show();
            returnCode = app.exec();
        }
        uninit();
    }
    else {
        qDebug() << "Application initialization failed";
    }
    return returnCode;
}

