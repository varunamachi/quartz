
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTreeView>
#include <QGroupBox>

#include <common/templating/TemplateUtils.h>
#include <common/templating/TemplateProcessor.h>
#include <common/templating/Template.h>
#include <common/templating/TemplateInstance.h>

#include <common/model_view/ArrayModel.h>

#include <plugin_base/BundleLoggin.h>

#include "TemplateManager.h"
#include "CreatorWidget.h"
#include "TemplateSelectorDialog.h"
#include "GenInfo.h"
#include "CodeGenerator.h"
#include "TemplateConfigWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

const QString QUARTZ_ROOT{ "QUARTZ_ROOT" };

const QString CreatorWidget::CONTENT_ID{ "qzp.creator.content.main" };
const QString CreatorWidget::CONTENT_NAME{ "PluginCreator" };
const QString CreatorWidget::CONTENT_KIND{ "meta" };

static inline bool isSource( const QString &name ) {
    return name.endsWith( ".cpp" )
            || name.endsWith( ".cxx" )
            || name.endsWith( ".cc" )
            || name.endsWith( "cx" );

}

struct CreatorWidget::Data
{
    explicit Data( std::shared_ptr< TemplateManager > tman,
                   CreatorWidget *parent )
        : m_fqIDEdit{ new QLineEdit{ parent }}
        , m_idEdit{ new QLineEdit{ parent }}
        , m_namespaceEdit{ new QLineEdit{ parent }}
        , m_nameEdit{ new QLineEdit{ parent }}
        , m_dirPath{ new QLineEdit{ parent }}
        , m_browseButton{ new QPushButton{ tr( "Browse "), parent }}
        , m_createButton{ new QPushButton{ tr( "Create" ), parent }}
        , m_templateManager{ tman }
        , m_templateSelector{ new TemplateSelectorDialog{ tman.get(), parent }}
        , m_configWidget{ new TemplateConfigWidget{ parent }}
        , m_globalConfig{ std::make_shared< GlobalConfig >() }
    {
    }

    QLineEdit *m_fqIDEdit;

    QLineEdit *m_idEdit;

    QLineEdit *m_namespaceEdit;

    QLineEdit *m_nameEdit;

    QLineEdit *m_dirPath;

    QPushButton *m_browseButton;

    QPushButton *m_createButton;

//    ArrayModel *m_tmodel;

    std::shared_ptr< TemplateManager > m_templateManager;

    TemplateSelectorDialog *m_templateSelector;

    TemplateConfigWidget *m_configWidget;

    std::shared_ptr< GlobalConfig > m_globalConfig;
};

void addStandaredTemplates( TemplateManager *tman )
{
    QStringList names;
    QDir inDir{ ":/resources" };
    auto list = inDir.entryInfoList( names );
    for( int i = 0; i < list.size(); ++ i ) {
        auto entry = list.at( i );
        if( entry.suffix() == "template" ) {
            auto key = entry.baseName();
            QFile file{ entry.absoluteFilePath() };
            auto content = QString{ file.readAll() };
            auto tmpl = std::make_shared< Template >( key, content );
            tman->addTemplate( tmpl );
        }
    }
}

inline void error( CreatorWidget *obj, const QString &msg )
{
    QMessageBox::critical( obj, QObject::tr( "Bundle Creator" ), msg );
}

inline void info( CreatorWidget *obj, const QString &msg )
{
    QMessageBox::information( obj, QObject::tr( "Bundle Creator" ), msg );
}

CreatorWidget::CreatorWidget( std::shared_ptr< TemplateManager > tman,
                              QWidget *parent)
    : ContentWidget( CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent )
    , m_data{ new Data{ tman, this }}
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

    //Configuration part
    auto addBtn = new QPushButton{ tr("Add Plugin"), this };
    auto addLyt = new QHBoxLayout{};
    addLyt->addStretch();
    addLyt->addWidget( addBtn );

    auto btnLyt = new QHBoxLayout{};
    btnLyt->addStretch();
    btnLyt->addWidget( m_data->m_createButton );

    auto configLyt = new QVBoxLayout{};
    configLyt->addLayout( addLyt );
    configLyt->addWidget( m_data->m_configWidget );
    configLyt->addLayout( btnLyt );

    auto gbx = new QGroupBox{ tr( "Confirure Plugins" ), this };
    gbx->setLayout( configLyt );


    //Main layout
    auto  mainLayout = new QVBoxLayout{};
    mainLayout->addWidget( new QLabel{ tr( "Create A Quartz Plugin: ")});
    mainLayout->addLayout( layout );
    mainLayout->addWidget( gbx );
    this->setLayout( mainLayout );

    //Setup initial state and validators
    m_data->m_fqIDEdit->setValidator(
                new QRegExpValidator{ QRegExp{ "^[a-z][a-z0-9_\\.]{0,30}$" }});
    m_data->m_idEdit->setEnabled( false );
    m_data->m_namespaceEdit->setEnabled( false );

    //Connections
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
    connect( addBtn, &QPushButton::clicked, [ this ](){
        m_data->m_templateSelector->exec();
        if( m_data->m_templateSelector->result() == QDialog::Accepted ) {
            this->addTemplates();
        }
        m_data->m_templateSelector->clearSelection();
    });

#ifdef QT_DEBUG
    auto testBundleLoc = QStandardPaths::writableLocation(
                QStandardPaths::TempLocation ) + "/qz_bundle/";
    m_data->m_idEdit->setText( "test" );
    m_data->m_fqIDEdit->setText( "test" );
    m_data->m_namespaceEdit->setText( "Test" );
    m_data->m_nameEdit->setText( "Test" );
    m_data->m_dirPath->setText( testBundleLoc );
#endif
    m_data->m_templateManager->loadCoreTemplates();
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
        m_data->m_dirPath->setText( dirPath );
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

    m_data->m_globalConfig->insert( "BUNDLE_ID", id );
    m_data->m_globalConfig->insert( "BUNDLE_NAME", name );
    m_data->m_globalConfig->insert( "BUNDLE_NAMESPACE", ns );
    m_data->m_globalConfig->insert( "BUNDLE_DISPLAY_NAME", display );
//    m_data->m_globalConfig->insert( "files", files );


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
    GenInfo info{ id, name, display, ns };
    QStringList sources, headers;
    for( auto i = 0; i < m_data->m_configWidget->numInstances(); ++ i ) {
        auto inst = m_data->m_configWidget->instanceAt( i );
        if( isSource( inst->name() )) {
            sources.append( inst->name() );
        }
        else if( inst->name() != "CMakeLists.txt" ){
            headers.append( inst->name() );
        }
        info.addTemplateInstance( inst );
    }
    m_data->m_globalConfig->insert( "sources", sources );
    m_data->m_globalConfig->insert( "headers", headers );
    CodeGenerator generator{ &info };
    auto result = generator.generate( path );
    if( result ) {
#ifndef QT_DEBUG
        //create the resource directory and place the plugin.txt there
        m_data->m_idEdit->clear();
        m_data->m_fqIDEdit->clear();
        m_data->m_namespaceEdit->clear();
        m_data->m_nameEdit->clear();
        m_data->m_dirPath->clear();
#endif
        QZP_INFO << "Created bundle with id " << id << " at " << path;
        auto msg = tr( "Bundle %1 created successfully" ).arg( id );
        QMessageBox::information( this, tr( "Bundle Creator"), msg );
    }
    else {
        QZP_ERROR << "Could not create plugin with " << id << " at " << path;
        QMessageBox::critical( this, tr( "Bundle Creator"),
                               generator.lastError());
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

void CreatorWidget::addTemplates()
{
    auto selected = m_data->m_templateSelector->selectedTemplates();
    foreach( auto t, selected) {
        auto inst = m_data->m_configWidget->createInstanceOf( t );
        inst->setGlobalConfig( m_data->m_globalConfig );
    }
}


} } }


//ActionBar          - AbstractActionItemProvider   - QuartzItem
//ConfigPageSelector - AbstractConfigPageProvider   - AbstractConfigPage
//ContentManager     - AbstractContentProvider      - ContentWidget
//GeneralNodelTree   - AbstractGeneralNodeProvider  - NodeInfo
//PageManager        - AbstractPageProvider         - QuartzPage
//SelectorManager    - AbstractSelectorProvider     - AbstractSelector
//TemplateManager    - AbstractTemplateProvider     - Template
//TitleBar           - AbstractTitleItemProvider    - QuartzItem
//ViewManager        - AbstractViewProvider         - QuartzView
