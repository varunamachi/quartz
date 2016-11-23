#include <QHash>
#include <QStackedLayout>

#include <core/logger/Logging.h>

#include "ContentWidget.h"
#include "AbstractContentProvider.h"
#include "ContentManager.h"

namespace Quartz {

struct ContentManager::Data
{
    explicit Data( QWidget *parent )
        : m_layout( new QStackedLayout{ parent })
    {

    }

    QHash< QString, ContentWidget *> m_widgets;

    QVector< ContentWidget *> m_fromPlugins;

    QStackedLayout *m_layout;
};

const QString ContentManager::ADAPTER_NAME{ "Content Manager" };

ContentManager::ContentManager( QWidget *parent )
    : QWidget( parent )
//    , m_data( std::make_unique< Data >() )
    , m_data( new Data{ this } )
{

}

ContentManager::~ContentManager()
{

}

bool ContentManager::addContent( ContentWidget *content )
{
    bool result = false;
    if( content != nullptr ) {
        m_data->m_widgets.insert( content->id(), content );
        auto index = m_data->m_layout->addWidget( content );
        m_data->m_layout->setCurrentIndex( index );
        result = true;
    }
    return result;
}

bool ContentManager::removeContent( const QString &contentId )
{
    bool result = false;
    auto content = m_data->m_widgets.value( contentId );
    if( content != nullptr ) {
        if( m_data->m_layout->currentWidget() == content
                && m_data->m_layout->count() > 0 ) {
                m_data->m_layout->setCurrentIndex( 0 );
        }
        m_data->m_widgets.remove( contentId );
        m_data->m_layout->removeWidget( content );
        result = true;
    }
    return result;
}

ContentWidget * ContentManager::content( const QString &contentId )
{
    ContentWidget * widget = m_data->m_widgets.value( contentId, nullptr );
    return widget;
}

QVector< ContentWidget *> ContentManager::contentsOfKind( const QString &kind )
{
    QVector< ContentWidget *> content;
    auto it = m_data->m_widgets.begin();
    for( ; it != m_data->m_widgets.end(); ++ it ) {
        if( it.value()->kind() == kind ) {
            content.push_back( it.value() );
        }
    }
    return content;
}

int ContentManager::removeKind( const QString &kind )
{
    int removed = 0;
    auto it = m_data->m_widgets.begin();
    for( ; it != m_data->m_widgets.end(); ++ it ) {
        if( it.value()->kind() == kind ) {
            m_data->m_widgets.erase( it );
            ++ removed;
        }
    }
    return removed;
}

void ContentManager::selectContent( const QString &contentId )
{
    auto widget = m_data->m_widgets.value( contentId );
    if( widget != nullptr ) {
        m_data->m_layout->setCurrentWidget( widget );
    }
}

const QString & ContentManager::pluginType() const
{
    return AbstractContentProvider::PLUGIN_TYPE;
}

const QString & ContentManager::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ContentManager::handlePlugin( AbstractPlugin *plugin )
{
    bool result = true;
    auto provider = dynamic_cast< AbstractContentProvider *>( plugin );
    if( provider != nullptr ) {
        auto contents = provider->widgets();
        foreach( auto content, contents ) {
            if( addContent( content )) {
                m_data->m_fromPlugins.push_back( content );
            }
            else {
                result = false;
            }
        }
    }
    else {
        auto pluginName = plugin != nullptr ? plugin->pluginId()
                                            : "<null>";
        QZ_ERROR( "Qz:ContentManager" )
                << "Invalid content plugin provided: "
                << pluginName;
    }
    return result;
}

bool ContentManager::finalizePlugins()
{
    auto result = true;
//    for( int i = 0; i < m_data->m_fromPlugins.size(); ++ i ) {
//        auto content = m_data->m_fromPlugins.at( i );
//        result = removeContent( content->id() ) && result;
//    }
    m_data->m_fromPlugins.clear();
    return result;
}

void ContentManager::setupLayout()
{
    auto layout = new QVBoxLayout();
    layout->addLayout( m_data->m_layout );
    layout->setContentsMargins( QMargins{ });
    m_data->m_layout->setContentsMargins( QMargins{ });
    this->setLayout( layout );
}


}
