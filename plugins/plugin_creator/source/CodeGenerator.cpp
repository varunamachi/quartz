
#include <QString>
#include <QDir>
#include <QFile>

#include <plugin_base/BundleLoggin.h>

#include <common/templating/AdvancedTemplateProcessor.h>
#include <common/templating/TemplateInstance.h>
#include <common/templating/Template.h>

#include "GenInfo.h"
#include "CodeGenerator.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct CodeGenerator::Data
{
    Data( const GenInfo *info )
        : m_info{ info }
    {

    }

    const GenInfo *m_info;

    QString m_lastError;
};

CodeGenerator::CodeGenerator( const GenInfo *info )
    : m_data{ new Data{ info }}
{

}

CodeGenerator::~CodeGenerator()
{

}

bool CodeGenerator::generate( const QString &path )
{
//    TemplateProcessor::Variables vars;
//    vars.insert( "BUNDLE_ID", m_data->m_info->id() );
//    vars.insert( "BUNDLE_NAME", m_data->m_info->name() );
//    vars.insert( "BUNDLE_NAMESPACE", m_data->m_info->ns() );
//    vars.insert( "BUNDLE_DISPLAY_NAME", m_data->m_info->display() );
//    QStringList classes;
//    classes << "PluginBundle";
//    vars.insert( "classes", classes );

//    QStringList files;
//    files << "#other files go here";
//    vars.insert( "files", files );

//    result = TemplateUtils::generateForDir(
//                vars,
//                QDir{ ":/resources" },
//                QDir{ path },
//                [ & ]( const QString &in ) -> QString {
//        if( in == "Plugin.cpp.template" ) {
//            return m_data->m_info->ns() + ".cpp";
//        }
//        else if( in == "resources.qrc.template" ) {
//            return m_data->m_info->name() + ".qrc";
//        }
//        return "";
//    });
    bool result = true;
    for( auto i = 0; i < m_data->m_info->numTemplateInstances(); ++ i ) {
        auto tinst = m_data->m_info->templateInstanceAt( i );
        result = this->generateForInstance( path, tinst ) && result;
    }
    if( result ) {
        QDir dir{ path };
        QString msg;
        if( dir.mkdir( "resources" )) {
            QFile ptxt{ dir.absoluteFilePath( "resources/plugin.txt" )};
            if( ptxt.open( QFile::ReadWrite )) {
                QTextStream fstream{ &ptxt };
                fstream << "#Created By Quartz Bundle Creator\n"
                        << "id=" << m_data->m_info->id()  << '\n'
                        << "name=" << m_data->m_info->name() << '\n'
                        << "display=" << m_data->m_info->display() << '\n'
                        << "ns=" << m_data->m_info->ns() << '\n'
                        << "version=0.0.0.0";
            }
            else {
                QZP_ERROR << "Failed to create plugin.txt at " <<
                             path << "/resources";
                m_data->m_lastError = QObject::tr(
                            "Failed to create plugin.txt in resource dir" );
                result = false;
            }
        }
        else {
            QZP_ERROR << "Failed to create resource directory at " << path;
            m_data->m_lastError =
                    QObject::tr( "Failed to create resource dir at %1" )
                        .arg( path );
            result = false;
        }
        if( ! result ) {
            this->m_data->m_lastError = msg;
        }
    }
    if( result ) {
        QZP_INFO << "Created bundle with id "
                 << m_data->m_info->id()
                 << " at " << path;
        m_data->m_lastError = QObject::tr(
                    "Bundle %1 created successfully" ).arg(
                        m_data->m_info->id() );
    }
    else {
        QZP_ERROR << "Could not create plugin with "
                  << m_data->m_info->id() << " at " << path;
        m_data->m_lastError = QObject::tr(
                    "Could not create bundle %1" ).arg( m_data->m_info->id() );

    }
    return result;
}

const QString & CodeGenerator::lastError() const
{
    return m_data->m_lastError;
}

bool CodeGenerator::generateForInstance( const QString &path,
                                         const TemplateInstance *instance )
{
    auto filePath = path + "/" + instance->name();
    QFile genFile{ filePath };
    if(  genFile.exists() ) {
        QZP_ERROR << "Could not generate file " << instance->name()
                  << ", target already exists at: " << filePath;
        m_data->m_lastError = QObject::tr(
                    "Template Generation: output file %1 already exist, cannot "
                    "overwrite").arg( path );
        return false;
    }
    if( ! genFile.open( QFile::ReadWrite )) {
        QZP_ERROR << "Could not generate file " << instance->name()
                  << ", failed to create" << filePath;
        m_data->m_lastError = QObject::tr(
                    "Template Generation: Failed to create file at %1")
                .arg( path );
        return false;
    }
    QTextStream stream{ &genFile };
    AdvancedTemplateProcessor tproc{ instance };
    auto result = tproc.process( stream );
    if( ! result ) {
        m_data->m_lastError = tproc.lastError();
    }
    return result;
}


} } }
