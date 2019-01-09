
#include <core/logger/Logging.h>

#include <common/widgets/QzScroller.h>
#include <common/widgets/StackedContainer.h>

#include "QuartzView.h"
#include "AbstractViewProvider.h"
#include "ViewManager.h"

namespace Quartz {

struct ViewManager::Data {
    explicit Data(AbstractContainer *container)
        : m_viewContainer(container)
    {

    }

    int m_height;

    int m_btnWidth;

    AbstractContainer *m_viewContainer;

    QHash< QString, QuartzView *> m_views;

    QMultiHash< QString, QuartzView *> m_categoriesToViews;

    QVector< QuartzView *> m_extensionViews;
};

const QString ViewManager::ADAPTER_NAME{ "qz.view_manager"};

ViewManager::ViewManager(AbstractContainer *container, QWidget *parent )
    : QWidget( parent )
    , m_data(std::make_unique<Data>(container))
{
    this->setVisible( false );
    auto layout = new QVBoxLayout{ this };
    layout->addWidget( m_data->m_viewContainer );
    layout->setContentsMargins( QMargins{} );
    m_data->m_viewContainer->setContentsMargins( QMargins{} );
    this->setContentsMargins( QMargins{ 2, 2, 2, 2 }) ;
    this->setLayout( layout );
}

ViewManager::~ViewManager()
{

}


void ViewManager::addView( QuartzView *view )
{
    if( view != nullptr ) {
        m_data->m_viewContainer->addWidget(
                    view->viewId(),
                    view->viewDisplayName(),
                    view->icon(),
                    view->activeIcon(),
                    view);
        m_data->m_views.insert( view->viewId(), view );
        this->setVisible( true );
    }
    else {
        QZ_ERROR( "Qz:ViewManager" ) << "Invalid view given";
    }
}


void ViewManager::removeView( const QString &viewId )
{
    QuartzView *view = m_data->m_views.value( viewId );
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
            m_data->m_viewContainer->removeWidget( view->viewId() );
            m_data->m_views.remove( view->viewId() );
            QZ_INFO( "Qz:ViewManager" )
                    << "succesfully removed view with id " << view->viewId()
                    << " of category " << view->viewCategoryId();
            if( m_data->m_views.empty() ) {
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
    QList< QuartzView *> views = m_data->m_categoriesToViews.values( categoryId );
    if( ! views.isEmpty() ) {
        for( QuartzView *view : views ) {
            m_data->m_views.remove( view->viewId() );
        }
        m_data->m_categoriesToViews.remove( categoryId );
        if( m_data->m_views.empty() ) {
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
    QuartzView *view = m_data->m_views.value( viewId );
    return view;
}


QList< QuartzView * > ViewManager::views() const
{
    QList< QuartzView *> views;
    auto it = m_data->m_views.begin();
    for( ; it != m_data->m_views.end(); ++ it ) {
        views.append( it.value() );
    }
    return views;
}


QList< QuartzView * > ViewManager::views( const QString &categoryId ) const
{
    QList< QuartzView *> views = m_data->m_categoriesToViews.values( categoryId );
    return views;
}


QuartzView * ViewManager::currentView() const
{
    QString viewId = m_data->m_viewContainer->currentId();
    QuartzView *view = m_data->m_views.value( viewId );
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
    QList< QString > categories = m_data->m_categoriesToViews.keys();
    return categories;
}


void ViewManager::selectView( QString viewId )
{
    if( m_data->m_views.contains( viewId ) ) {
        m_data->m_viewContainer->select( viewId );
    }
    else {
        QZ_ERROR( "Qz:ViewManager" )
                << "Could not find a view with id " << viewId;
    }
}

const QString & ViewManager::extensionType() const
{
    return AbstractViewProvider::EXTENSION_TYPE;
}

const QString & ViewManager::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool ViewManager::handleExtension( Ext::Extension *extension )
{
    auto result = false;
    auto provider = dynamic_cast< AbstractViewProvider *>( extension );
    if( provider != nullptr ) {
        auto views = provider->views();
        foreach( auto view, views ) {
            addView( view );
            m_data->m_extensionViews.push_back( view );
        }
        result = true;
    }
    else {
        auto extensionName = extension != nullptr ? extension->extensionId()
                                            : "<null>";
        QZ_ERROR( "Qz:ViewManager" )
                << "Invalid view extension provided: " << extensionName;
    }
    return result;
}

bool ViewManager::finalizeExtension()
{
//    for( int i = 0; i < m_data->m_extensionViews.size(); ++ i ) {
//        auto view = m_data->m_extensionViews.at( i );
//        removeView( view );
//    }
    m_data->m_extensionViews.clear();
    return true;
}

}


