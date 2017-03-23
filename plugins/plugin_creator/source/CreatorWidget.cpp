
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "CreatorWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

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
    layout->addWidget( new QLabel{ "", this  }, 4, 0 );
    layout->addWidget( m_data->m_createButton, 4, 1 );

    this->setLayout( layout );

    //PluginNamespace
    //plugin_id
    //Plugin Name

}

CreatorWidget::~CreatorWidget()
{

}



} } }
