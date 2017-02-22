#include <QVBoxLayout>
#include <QLabel>
#include <QQuickView>
#include <QQuickWidget>

#include "ContentProvider.h"

namespace Quartz { namespace OrekClient {

const QString OrekContent::CONTENT_ID{ "qzp.orekclient.content" };
const QString OrekContent::CONTENT_NAME{ "Orek" };
const QString OrekContent::CONTENT_KIND{ "orek" };

OrekContent::OrekContent( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
{
//    QQuickView *view = new QQuickView();
//    view->setSource( QUrl{ "qrc:/qml/OrekMainPage.qml" });
//    QWidget *container = QWidget::createWindowContainer( view, this );
//    container->setFocusPolicy( Qt::TabFocus );
//    container->setAttribute( Qt::WA_TranslucentBackground,
//                             false );

    auto container = new QQuickWidget{ this };
    container->setSource( QUrl{ "qrc:/qml/OrekMainPage.qml" });
    container->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    container->setAttribute(Qt::WA_AlwaysStackOnTop);
//    container->setClearColor(Qt::transparent);
//    container->setStyleSheet( "background-color: red;" );

    auto layout = new QVBoxLayout{ };
    layout->addWidget( container );
    this->setLayout( layout );
    this->setContentsMargins( QMargins{} );
    container->setContentsMargins( QMargins{} );

    //    container->raise();
    container->resize(400, 222);
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
