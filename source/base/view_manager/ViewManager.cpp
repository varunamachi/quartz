
#include <core/logger/Logging.h>

#include <common/widgets/QzScroller.h>
#include <common/widgets/StackedContainer.h>

#include "QuartzView.h"
#include "AbstractViewProvider.h"
#include "ViewManager.h"

namespace Quartz {

const QString ViewManager::ADAPTER_NAME{ "qz.title_bar" };

ViewManager::ViewManager( AbstractContainer *container,
                          QWidget *parent )
    : QWidget( parent )
    , m_viewContainer( container )
{
    this->setVisible( false );
    auto layout = new QVBoxLayout{ this };
    layout->addWidget( m_viewContainer );
    layout->setContentsMargins( QMargins{} );
    m_viewContainer->setContentsMargins( QMargins{} );
    this->setContentsMargins( QMargins{ 2, 2, 2, 2 }) ;
    this->setLayout( layout );
}


void ViewManager::addView( QuartzView *view )
{
    if( view != nullptr ) {
        m_viewContainer->addWidget( view->viewId(),
                                    view->viewDisplayName(),
                                    view );
        m_views.insert( view->viewId(), view );
        this->setVisible( true );
    }
    else {
        QZ_ERROR( "Qz:ViewManager" ) << "Invalid view given";
    }
}


void ViewManager::removeView( const QString &viewId )
{
    QuartzView *view = m_views.value( viewId );
    if( view != nullptr ) {
        removeView( viewId );
    }
    else {
        QZ_ERROR( "QzApp:ViewManager" )
                << "Could not remove view with id " << viewId << ". No view "
                   " with given ID found";
    }
}


void ViewManager::removeView( QuartzView *view )
{
    if( view != nullptr ) {
            m_viewContainer->removeWidget( view->viewId() );
            m_views.remove( view->viewId() );
            QZ_INFO( "Qz:ViewManager" )
                    << "succesfully removed view with id " << view->viewId()
                    << " of category " << view->viewCategoryId();
            if( m_views.empty() ) {
                this->setVisible( false );
            }
    }
    else {
        QZ_ERROR( "Qz:ViewManager" )
                << "Could not remove view with id " << ". Invalid view given";
    }
}


void ViewManager::removeViewCategory( const QString &categoryId )
{
    QList< QuartzView *> views = m_categoriesToViews.values( categoryId );
    if( ! views.isEmpty() ) {
        for( QuartzView *view : views ) {
            m_views.remove( view->viewId() );
        }
        m_categoriesToViews.remove( categoryId );
        if( m_views.empty() ) {
            this->setVisible( false );
        }
    }
    else {
        QZ_ERROR( "Qz:ViewManager" )
                << "Could not remove category " << categoryId
                << ". No such category found";
    }
}


QuartzView * ViewManager::view( const QString &viewId ) const
{
    QuartzView *view = m_views.value( viewId );
    return view;
}


QList< QuartzView * > ViewManager::views() const
{
    QList< QuartzView *> views;
    auto it = m_views.begin();
    for( ; it != m_views.end(); ++ it ) {
        views.append( it.value() );
    }
    return views;
}


QList< QuartzView * > ViewManager::views( const QString &categoryId ) const
{
    QList< QuartzView *> views = m_categoriesToViews.values( categoryId );
    return views;
}


QuartzView * ViewManager::currentView() const
{
    QString viewId = m_viewContainer->currentId();
    QuartzView *view = m_views.value( viewId );
    return view;
}


const QString ViewManager::currentCategory() const
{
    QString curCategory = "";
    QuartzView *curView = currentView();
    if( curView != nullptr ) {
        curCategory = curView->viewCategoryId();
    }
    return curCategory;
}


QList< QString > ViewManager::categories() const
{
    QList< QString > categories = m_categoriesToViews.keys();
    return categories;
}


void ViewManager::selectView( QString viewId )
{
    if( m_views.contains( viewId ) ) {
        m_viewContainer->select( viewId );
    }
    else {
        QZ_ERROR( "Qz:ViewManager" )
                << "Could not find a view with id " << viewId;
    }
}

const QString & ViewManager::pluginType() const
{
    return AbstractViewProvider::PLUGIN_TYPE;
}

const QString & ViewManager::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ViewManager::handlePlugin( AbstractPlugin *plugin )
{
    auto result = false;
    auto provider = dynamic_cast< AbstractViewProvider *>( plugin );
    if( provider != nullptr ) {
        auto views = provider->views();
        foreach( auto view, views ) {
            addView( view );
            m_pluginViews.push_back( view );
        }
        result = true;
    }
    else {
        auto pluginName = plugin != nullptr ? plugin->pluginId()
                                            : "<null>";
        QZ_ERROR( "Qz:ViewManager" )
                << "Invalid view plugin provided: " << pluginName;
    }
    return result;
}

bool ViewManager::finalizePlugins()
{
//    for( int i = 0; i < m_pluginViews.size(); ++ i ) {
//        auto view = m_pluginViews.at( i );
//        removeView( view );
//    }
    m_pluginViews.clear();
    return true;
}

}


