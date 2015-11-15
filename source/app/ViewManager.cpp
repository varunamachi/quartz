
#include <vqcore/logger/VQLogger.h>

#include "ViewManager.h"

namespace Vam { namespace Quartz {

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
        VQ_ERROR( "Qz:ViewManager" ) << "Invalid view given";
    }
}


void ViewManager::removeView( const QString &viewId )
{
    QuartzView *view = m_views.value( viewId );
    if( view != nullptr ) {
        removeView( viewId );
    }
    else {
        VQ_ERROR( "QzApp:ViewManager" )
                << "Could not remove view with id " << viewId << ". No view "
                   " with given ID found";
    }
}


void ViewManager::removeView( QuartzView *view )
{
    if( view != nullptr ) {
            m_viewContainer->removeWidget( view->viewId() );
            m_views.remove( view->viewId() );
            VQ_INFO( "Qz:ViewManager" )
                    << "succesfully removed view with id " << view->viewId()
                    << " of category " << view->viewCategoryId();
    }
    else {
        VQ_ERROR( "Qz:ViewManager" )
                << "Could not remove view with id " << ". Invalid view given";
    }
}


void ViewManager::removeViewCategory( const QString &categoryId )
{
    StackedContainer *container = m_viewContainers.value( categoryId );
    if( container != nullptr ) {
        QList< QString > allIds = container->allIds();
        for( const QString &id : allIds ) {
            m_views.remove( id );
        }
        m_viewContainers.remove( categoryId );
        delete container;
    }
    else {
        VQ_ERROR( "Qz:ViewManager" )
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
    QList< QuartzView *> views;
    for( auto it = m_views.begin(); it != m_views.end(); ++ it ) {
        QuartzView *view = it.value();
        if( view->viewCategoryId() == categoryId ) {
            views.append( view );
        }
    }
    return views;
}


QuartzView * ViewManager::currentView() const
{
    QuartzView *view = nullptr;
    QString curCategory = m_viewContainer->currentId();
    if( ! curCategory.isEmpty() ) {
        StackedContainer *viewContnr = m_viewContainers.value( curCategory );
        if( viewContnr != nullptr ) {
            QString curViewId = viewContnr->currentId();
            QWidget *widget = viewContnr->widget( curViewId );
            view = dynamic_cast< QuartzView *>( widget );
        }
        else {
            VQ_ERROR( "Qz:ViewManager" )
                    << "Could not retrieve current view, there are no views in "
                       "the current category"
                    << curCategory;
        }
    }
    else {
        VQ_ERROR( "Qz:ViewManager" )
                << "Could not retrieve current view There are no categories "
                   "registered" << curCategory;
    }
}


const QString & ViewManager::currentCategory() const
{
    const QString &curCategory = m_viewContainer->currentId();
    return curCategory;
}


QStringList ViewManager::categories() const
{
    QStringList categoies;
    auto it = m_viewContainers.begin();
    for( ; it != m_viewContainers.end(); ++ it ) {
        categoies.append( it.key() );
    }
    return categoies;
}


void ViewManager::selectCategory( QString categoryId )
{
    m_viewContainer->select( categoryId );
}


void ViewManager::selectView( QString viewId )
{
    bool result = false;
    QuartzView *view = m_views.value( viewId );
    if( view != nullptr ) {
        selectCategory( view->viewCategoryId() );
        StackedContainer *viewCont = m_viewContainers.value(
                    view->viewCategoryId() );
        if( viewCont ) {
            viewCont->select( viewId );
            result = true;
        }
    }
    if( ! result ){
        VQ_ERROR( "Qz:ViewManager" )
                << "Could not find a view with id " << viewId;
    }
}


} }


