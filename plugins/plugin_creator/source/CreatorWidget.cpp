
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QRegExpValidator>

#include <core/templating/TemplateUtils.h>
#include <core/templating/TemplateProcessor.h>

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
        : m_idEdit{ new QLineEdit{ parent }}
        , m_namespaceEdit{ new QLineEdit{ parent }}
        , m_nameEdit{ new QLineEdit{ parent }}
        , m_dirPath{ new QLineEdit{ parent }}
        , m_browseButton{ new QPushButton{ tr( "Browse "), parent }}
        , m_createButton{ new QPushButton{ tr( "Create" ), parent }}
    {

    }

    QLineEdit *m_idEdit;

    QLineEdit *m_namespaceEdit;

    QLineEdit *m_nameEdit;

    QLineEdit *m_dirPath;

    QPushButton *m_browseButton;

    QPushButton *m_createButton;

};

CreatorWidget::CreatorWidget(QWidget *parent)
    : ContentWidget( CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent )
    , m_data{ new Data{ this }}
{
    auto layout = new QGridLayout{ };
    layout->addWidget( new QLabel{ tr( "Plugin ID" ), this }, 0, 0 );
    layout->addWidget( m_data->m_idEdit, 0, 1 );
    layout->addWidget( new QLabel{ tr( "Plugin Namespace" ), this }, 1, 0 );
    layout->addWidget( m_data->m_namespaceEdit, 1, 1 );
    layout->addWidget( new QLabel{ tr( "Plugin Name" ), this }, 2, 0 );
    layout->addWidget( m_data->m_nameEdit, 2, 1 );

    auto browseLayout = new QHBoxLayout{};
    browseLayout->addWidget( m_data->m_dirPath );
    browseLayout->addWidget( m_data->m_browseButton );

    layout->addWidget( new QLabel{ tr( "Plugin Path" ), this }, 3, 0 );
    layout->addLayout( browseLayout , 3, 1 );

    auto  mainLayout = new QVBoxLayout{};
    mainLayout->addWidget( new QLabel{ tr( "Create Plugin: ")});
    mainLayout->addLayout( layout );
    mainLayout->addWidget( m_data->m_createButton );
    mainLayout->addStretch();

    this->setLayout( mainLayout );

    m_data->m_idEdit->setValidator(
                new QRegExpValidator{ QRegExp{ "^[a-z][a-z0-9_\\-]{0,30}$" }});
    m_data->m_namespaceEdit->setValidator(
                new QRegExpValidator{ QRegExp{ "^[A-Z][a-zA-Z0-9]{0,30}$" }});

    connect( m_data->m_browseButton,
             &QPushButton::released,
             this,
             &CreatorWidget::onBrowse );
    connect( m_data->m_createButton,
             &QPushButton::released,
             this,
             &CreatorWidget::onCreate );
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
    const auto id   = m_data->m_idEdit->text();
    const auto ns   = m_data->m_namespaceEdit->text();
    const auto name = m_data->m_nameEdit->text();
    const auto path = m_data->m_dirPath->text();
    QFileInfo dirInfo{ path };
    if( dirInfo.exists() && ! dirInfo.isDir() ) {
        QZP_ERROR << "Bundle destination " << path << "is not a directory";
    }

    TemplateProcessor::Variables vars;
    vars.insert( "PLUGIN_ID", id );
    vars.insert( "PLUGIN_NAMESPACE", ns );
    vars.insert( "PLUGIN_NAME", name );
    bool result = TemplateUtils::generateForDir(
                vars,
                QDir{ ":/" },
                QDir{ path });
    if( result ) {
        //create the resource directory and place the plugin.txt there
        m_data->m_idEdit->clear();
        m_data->m_namespaceEdit->clear();
        m_data->m_nameEdit->clear();
        m_data->m_dirPath->clear();
        QZP_INFO << "Created bundle with id " << id << " at " << path;
    }
    else {
        QZP_ERROR << "Could not create plugin with " << id << " at " << path;
    }

}



} } }
