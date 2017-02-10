#include <QVBoxLayout>
#include <QLabel>
#include <QQuickWidget>
#include "ContentProvider.h"

namespace Quartz { namespace OrekClient {

const QString OrekContent::CONTENT_ID{ "qzp.orekclient.content" };
const QString OrekContent::CONTENT_NAME{ "Orek" };
const QString OrekContent::CONTENT_KIND{ "orek" };

OrekContent::OrekContent( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
{
    auto layout = new QVBoxLayout{ };
    auto quickWidget = new QQuickWidget{ QUrl{ "qrc:/qml/main.qml" }, this };
    layout->addWidget( quickWidget );
    this->setLayout( layout );

    this->setContentsMargins( QMargins{} );
    quickWidget->setContentsMargins( QMargins{} );
}


struct ContentProvider::Data
{
    Data()
    {
        m_contents.push_back( new OrekContent{} );
    }

    QVector< ContentWidget *> m_contents;
};


/********************** Provider ************************************/
const QString ContentProvider::PLUGIN_ID{
    "qzp.orekclient.provider.content" };
const QString ContentProvider::PLUGIN_NAME{
    "Orek Content" };

ContentProvider::ContentProvider()
    : AbstractContentProvider{ PLUGIN_ID, PLUGIN_NAME }
    , m_data( new Data{} )
{

}

ContentProvider::~ContentProvider()
{

}

bool ContentProvider::init()
{
    return true;
}

bool ContentProvider::destroy()
{
    return true;
}

QVector< ContentWidget *> ContentProvider::widgets()
{
    return m_data->m_contents;
}



} }
