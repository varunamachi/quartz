
#include <core/logger/Logger.h>

#include <common/widgets/QzScroller.h>
#include <common/widgets/StackedContainer.h>

#include "QuartzView.h"
#include "AbstractViewProvider.h"
#include "ViewManager.h"

namespace Quartz {

const QString ViewManager::ADAPTER_NAME{ "quartz.title_bar" };

ViewManager::ViewManager( int height,
                          int btnWidth,
                          QWidget *parent )
    : m_height( height )
    , m_btnWidth( btnWidth )
    , m_viewContainer( new StackedContainer(
                           m_height,
                           m_btnWidth,
                           Qt::Horizontal,
                           this ))
    , QWidget( parent )
{

}


void ViewManager::addView( QuartzView *view )
{
    if( view != nullptr ) {
        m_viewContainer->addWidget( view->viewId(),
                                    view->viewDisplayName(),
                                    view );
        m_views.insert( view->viewId(), view );
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

bool ViewManager::handlePlugin( IPlugin *plugin )
{
    auto result = false;
    auto provider = dynamic_cast< AbstractViewProvider *>( plugin );
    if( provider != nullptr ) {
        auto view = provider->view();
        if( view != nullptr ) {
            addView( view );
            m_pluginViews.push_back( view );
            result = true;
        }
    }
    return result;
}

bool ViewManager::finalizePlugins()
{
    for( int i = 0; i < m_pluginViews.size(); ++ i ) {
        auto view = m_pluginViews.at( i );
        removeView( view);
    }
    return true;
}

}


