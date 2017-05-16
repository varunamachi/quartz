
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QRegExpValidator>
#include <QMessageBox>

#include <common/templating/TemplateUtils.h>
#include <common/templating/TemplateProcessor.h>

#include <plugin_base/BundleLoggin.h>

#include "CreatorWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

const QString QUARTZ_ROOT{ "QUARTZ_ROOT" };

const QString CreatorWidget::CONTENT_ID{ "qzp.creator.content.main" };
const QString CreatorWidget::CONTENT_NAME{ "PluginCreator" };
const QString CreatorWidget::CONTENT_KIND{ "meta" };

struct CreatorWidget::Data
{
    explicit Data( CreatorWidget *parent )
        : m_fqIDEdit{ new QLineEdit{ parent }}
        , m_idEdit{ new QLineEdit{ parent }}
        , m_namespaceEdit{ new QLineEdit{ parent }}
        , m_nameEdit{ new QLineEdit{ parent }}
        , m_dirPath{ new QLineEdit{ parent }}
        , m_browseButton{ new QPushButton{ tr( "Browse "), parent }}
        , m_createButton{ new QPushButton{ tr( "Create" ), parent }}
    {

    }
    QLineEdit *m_fqIDEdit;

    QLineEdit *m_idEdit;

    QLineEdit *m_namespaceEdit;

    QLineEdit *m_nameEdit;

    QLineEdit *m_dirPath;

    QPushButton *m_browseButton;

    QPushButton *m_createButton;

};

inline void error( CreatorWidget *obj, const QString &msg )
{
    QMessageBox::critical( obj, QObject::tr( "Bundle Creator" ), msg );
}

inline void info( CreatorWidget *obj, const QString &msg )
{
    QMessageBox::information( obj, QObject::tr( "Bundle Creator" ), msg );
}

CreatorWidget::CreatorWidget(QWidget *parent)
    : ContentWidget( CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent )
    , m_data{ new Data{ this }}
{
    auto browseLayout = new QHBoxLayout{};
    browseLayout->addWidget( m_data->m_dirPath );
    browseLayout->addWidget( m_data->m_browseButton );

    auto layout = new QGridLayout{ };
    int row = 0;
    layout->addWidget( new QLabel{ tr( "Fully Qualified Bundle ID ")}, row, 0 );
    layout->addWidget( m_data->m_fqIDEdit, row, 1 );
    ++ row;

    layout->addWidget( new QLabel{ tr( "Unique Name" ), this }, row, 0 );
    layout->addWidget( m_data->m_idEdit, row, 1 );
    ++ row;

    layout->addWidget( new QLabel{ tr( "Code Namespace" ), this }, row, 0 );
    layout->addWidget( m_data->m_namespaceEdit, row, 1 );
    ++ row;

    layout->addWidget( new QLabel{ tr( "Bundle Name" ), this }, row, 0 );
    layout->addWidget( m_data->m_nameEdit, row, 1 );
    ++ row;

    layout->addWidget( new QLabel{ tr( "Bundle Project Path" ), this }, row, 0);
    layout->addLayout( browseLayout , row, 1 );
    ++ row;

    auto  mainLayout = new QVBoxLayout{};
    mainLayout->addWidget( new QLabel{ tr( "Create A Quartz Bundle: ")});
    mainLayout->addLayout( layout );
    mainLayout->addWidget( m_data->m_createButton );
    mainLayout->addStretch();

    this->setLayout( mainLayout );

    m_data->m_fqIDEdit->setValidator(
                new QRegExpValidator{ QRegExp{ "^[a-z][a-z0-9_\\.]{0,30}$" }});
    m_data->m_idEdit->setEnabled( false );
    m_data->m_namespaceEdit->setEnabled( false );
//    m_data->m_idEdit->setValidator(
//                new QRegExpValidator{ QRegExp{ "^[a-z][a-z0-9_]{0,30}$" }});
//    m_data->m_namespaceEdit->setValidator(
//                new QRegExpValidator{ QRegExp{ "^[A-Z][a-zA-Z0-9]{0,30}$" }});

    connect( m_data->m_browseButton,
             &QPushButton::released,
             this,
             &CreatorWidget::onBrowse );
    connect( m_data->m_createButton,
             &QPushButton::released,
             this,
             &CreatorWidget::onCreate );
    connect( m_data->m_fqIDEdit,
             &QLineEdit::textChanged,
             this,
             &CreatorWidget::autoPopulate );
}

CreatorWidget::~CreatorWidget()
{

}

void CreatorWidget::onBrowse()
{
    QString dirPath = m_data->m_dirPath->text().trimmed();
    //Default directory priority:
    //  1. Previously selected
    //  2. QUARTZ_ROOT
    //  3. Platform Document location
    if( dirPath.isEmpty() || ! QFile::exists( dirPath )) {
        auto  env = QProcessEnvironment::systemEnvironment();
        auto qzRoot = env.value( QUARTZ_ROOT );
        QFileInfo info{ qzRoot };
        if( info.exists() && info.isDir() ) {
            dirPath = info.absoluteFilePath();
        }
        else {
            dirPath = QStandardPaths::writableLocation(
                        QStandardPaths::DocumentsLocation );
        }
    }
    dirPath = QFileDialog::getExistingDirectory(
                this,
                tr( "Plugin Source Location" ),
                dirPath );
    if( ! dirPath.isEmpty() ) {
        m_data->m_dirPath->setText( dirPath );\
    }
}

void CreatorWidget::onCreate()
{
    const auto id   = m_data->m_fqIDEdit->text();
    const auto name = m_data->m_idEdit->text();
    const auto ns   = m_data->m_namespaceEdit->text();
    const auto display = m_data->m_nameEdit->text();
    auto path = m_data->m_dirPath->text();
    auto dirName = "plugin_" + name;

    if( ! path.endsWith( dirName, Qt::CaseInsensitive )) {
        path = path + "/" + dirName;
    }
    path = path + "/source";
    QFileInfo dirInfo{ path };
    QDir dir{ path };
    if( id.isEmpty() || ns.isEmpty() || display.isEmpty() ) {
        auto empty = id.isEmpty() ? tr( "bundle ID" )
                                  : ns.isEmpty() ? tr( "bundle namespace" )
                                                 : tr( "bundle name" );
        auto msg = tr( "Invalid %1 given, cannot create bundle" ).arg( empty );
        error( this, msg );
        return;

    }
    if( dirInfo.exists() ) {
        auto msg = tr( "A file/directory already exists at %1,"
                       "do you want to overwrite it?" ).arg( path );
        auto ans = QMessageBox::question( this, tr( "Bundle Creator" ), msg );
        if( ans != QMessageBox::Yes ) {
            QZP_DEBUG << "Could not create bundle directory without deleting "
                         "existing directory at " << path;
            return;
        }
        else {
            if( dirInfo.isDir() ) {
                if( ! dir.removeRecursively() ) {
                    QZP_ERROR << "Failed to delete existing directory at "
                              << path;
                    msg = tr( "Failed to delete existing directory at %1" )
                            .arg( path );
                    error( this, msg );
                    return;
                }
                else {
                    QZP_DEBUG<< "Removed existing directory " << path;
                }
            }
            else {
                if( ! QFile::remove( path )) {
                    QZP_ERROR << "Failed to delete existing file at "
                              << path;
                    msg = tr( "Failed to delete existing file at %1" )
                            .arg( path );
                    error( this, msg );
                    return;
                }
                else {
                    QZP_DEBUG<< "Removed existing file" << path;
                }
            }
        }
    }
    if( ! dir.exists() && ! QDir{}.mkpath( path )) {
        QZP_ERROR << "Could not create bundle directory at " << path;
        auto msg = tr( "Could not create bundle directory at %1" ).arg( path );
        error( this, msg );
        return;
    }

    TemplateProcessor::Variables vars;
    vars.insert( "BUNDLE_ID", id );
    vars.insert( "BUNDLE_NAME", name );
    vars.insert( "BUNDLE_NAMESPACE", ns );
    vars.insert( "BUNDLE_DISPLAY_NAME", display );
    QStringList files;
    files << "one" << "two" << "three";
    vars.insert( "files", files );
    bool result = TemplateUtils::generateForDir(
                vars,
                QDir{ ":/resources" },
                QDir{ path },
                [ & ]( const QString &in ) -> QString {
        if( in == "Plugin.cpp.template" ) {
            return ns + ".cpp";
        }
        else if( in == "resources.qrc.template" ) {
            return name + ".qrc";
        }
        return "";
    });
    if( result ) {
        QString msg;
        if( dir.mkdir( "resources" )) {
            QFile ptxt{ dir.absoluteFilePath( "resources/plugin.txt" )};
            if( ptxt.open( QFile::ReadWrite )) {
                QTextStream fstream{ &ptxt };
                fstream << "#Created By Quartz Bundle Creator\n"
                        << "id=" << id << '\n'
                        << "name=" << name << '\n'
                        << "display=" << display << '\n'
                        << "ns=" << ns << '\n'
                        << "version=0.0.0.0";
            }
            else {
                QZP_ERROR << "Failed to create plugin.txt at " <<
                             path << "/resources";
                msg = tr( "Failed to create plugin.txt in resource dir" );
                result = false;
            }
        }
        else {
            QZP_ERROR << "Failed to create resource directory at " << path;
            msg = tr( "Failed to create resource dir at %1" ).arg( path );
            result = false;
        }
        if( ! result ) {
            error( this, msg );
        }
    }
    if( result ) {
        //create the resource directory and place the plugin.txt there
        m_data->m_idEdit->clear();
        m_data->m_fqIDEdit->clear();
        m_data->m_namespaceEdit->clear();
        m_data->m_nameEdit->clear();
        m_data->m_dirPath->clear();
        QZP_INFO << "Created bundle with id " << id << " at " << path;
        auto msg = tr( "Bundle %1 created successfully" ).arg( id );
        QMessageBox::information( this, tr( "Bundle Creator"), msg );
    }
    else {
        QZP_ERROR << "Could not create plugin with " << id << " at " << path;
        auto msg = tr( "Could not create bundle %1" ).arg( id );
        QMessageBox::critical( this, tr( "Bundle Creator"), msg );
    }
}

void CreatorWidget::autoPopulate( const QString &fqid )
{
    auto uniqueName = fqid;
    auto list = fqid.split( "." );
    if( list.size() ) {
        uniqueName = list.last();
    }
    auto nameCmp = uniqueName.split( "_" );
    QString ns;
    QString display;
    QTextStream nameStream{ &display };
    QTextStream nsStream{ &ns };
    for( int i = 0; i < nameCmp.size(); ++ i ) {
        auto word = nameCmp.at( i );
        if( ! word.isEmpty() ) {
            nsStream << word.at( 0 ).toUpper();
            nameStream << word.at( 0 ).toUpper();
            if( word.size() > 1 ) {
                nsStream << word.mid( 1 );
                nameStream << word.mid( 1 );
            }
            nameStream << ' ';
        }
    }
    m_data->m_idEdit->setText( uniqueName );
    m_data->m_namespaceEdit->setText( ns );
    m_data->m_nameEdit->setText( display );
}


} } }
