#include <QHash>


#include "ContentWidget.h"
#include "AbstractContentProvider.h"
#include "ContentManager.h"

namespace Quartz {

struct ContentManager::Data
{
    QHash< QString, ContentWidget *> m_widgets;

    QVector< ContentWidget *> m_fromPlugins;
};

const QString ContentManager::ADAPTER_NAME{ "Content Manager" };

ContentManager::ContentManager( QWidget *parent )
//    : m_data( std::make_unique< Data >() )
    : m_data( new Data{} )
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
        result = true;
    }
    return result;
}

bool ContentManager::removeContent( const QString &contentId )
{
    bool result = false;
    if( m_data->m_widgets.contains( contentId )) {
        m_data->m_widgets.remove( contentId );
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


const QString & ContentManager::pluginType() const
{
    return AbstractContentProvider::PLUGIN_TYPE;
}

const QString & ContentManager::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ContentManager::handlePlugin( IPlugin *plugin )
{
    bool result = false;
    auto provider = dynamic_cast< AbstractContentProvider *>( plugin );
    if( provider != nullptr ) {
        auto content = provider->widget();
        if( addContent( content )) {
            m_data->m_fromPlugins.push_back( content );
            result = true;
        }
    }
    return result;
}

bool ContentManager::finalizePlugins()
{
    auto result = true;
    for( int i = 0; i < m_data->m_fromPlugins.size(); ++ i ) {
        auto content = m_data->m_fromPlugins.at( i );
        result = removeContent( content->id() ) && result;
    }
    return result;
}


}
