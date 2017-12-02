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
        m_data->m_layout->addWidget( content );
        emit sigContentAdded( content );
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
        emit sigContentRemoved( contentId );
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
            auto id = it.value()->id();
            m_data->m_widgets.erase( it );
            emit sigContentRemoved( id );
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
        emit sigContentSelected( widget );
    }
}

const QString & ContentManager::extensionType() const
{
    return AbstractContentProvider::EXTENSION_TYPE;
}

const QString & ContentManager::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool ContentManager::handleExtension( Ext::Extension *ext )
{
    bool result = true;
    auto provider = dynamic_cast< AbstractContentProvider *>( ext  );
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
        auto pluginName = ext != nullptr ? ext->extensionId()
                                         : "<null>";
        QZ_ERROR( "Qz:ContentManager" )
                << "Invalid content plugin provided: "
                << pluginName;
    }
    return result;
}

bool ContentManager::finalizeExtension()
{
    auto result = true;
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
