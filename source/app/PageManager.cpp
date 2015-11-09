
#include <vqcore/logger/VQLogger.h>

#include "PageManager.h"

namespace Vam { namespace Quartz {

PageManager::PageManager( int categoryWidth,
                          int pagerHeight,
                          QWidget *parent )
    : m_selectorWidth( categoryWidth )
    , m_holderHeight( pagerHeight )
    , QWidget( parent )
{

}


void PageManager::addPage( QuartzPage *page )
{
    if( page != nullptr ) {
        StackedContainer *container = m_pageContainers.value(
                    page->pageCategoryName() );
        if( container == nullptr ) {
            container = new StackedContainer( 60, 150, Qt::Horizontal, this );
            m_catContainer->addWidget( page->pageCategoryId(),
                                       page->pageCategoryName(),
                                       container );

        }
        container->addWidget( page->pageId(), page->pageDisplayName(), page );
        m_pages.insert( page->pageId(), page );
    }
    else {
        VQ_ERROR( "Qz:PageManager" ) << "Invalid page given";
    }
}


void PageManager::removePage( const QString &pageId )
{
    QuartzPage *page = m_pages.value( pageId );
    if( page != nullptr ) {
        removePage( pageId );
    }
    else {
        VQ_ERROR( "QzApp:PageMan" )
                << "Could not remove page with id " << pageId << ". No page "
                   " with given ID found";
    }
}


void PageManager::removePage( QuartzPage *page )
{
    if( page != nullptr ) {
        StackedContainer *container =
                m_pageContainers.value( page->pageCategoryId() );
        if( container ) {
            container->removeWidget( page->pageId() );
            m_pages.remove( page->pageId() );
            if( container->isEmpty() ) {
                VQ_INFO( "Qz:PageManager" )
                        << "There are no pages left in the category with id "
                        << page->pageCategoryId() << ". The container for this "
                        << " category will be removed";
                m_pageContainers.remove( page->pageCategoryId() );
                delete container;
            }
        }
        else {
            VQ_ERROR( "Qz:PageManager" )
                    << "Could not remove page with ID " << page->pageId()
                    << ". Could not find the category of the page - "
                    << page->pageCategoryId();

        }
        VQ_INFO( "Qz:PageManager" )
                << "succesfully added  Page with id " << page->pageId()
                << " of category " << page->pageCategoryId();
    }
    else {
        VQ_ERROR( "Qz:PageManager" )
                << "Could not remove page with id " << ". Invalid page given";
    }
}


void PageManager::removePageCategory( const QString &categoryId )
{
}


QuartzPage * PageManager::page( const QString &pageId ) const
{
    return nullptr;
}


QList< QuartzPage * > PageManager::pages()
{
    QList< QuartzPage *> pages;
    return pages;
}


QList< QuartzPage * > PageManager::pages( const QString &categoryId ) const
{
    QList< QuartzPage *> pages;
    return pages;
}


QuartzPage * PageManager::currentPage() const
{
    return nullptr;

}


const QString PageManager::currentCategory() const
{
    return QString( "" );
}


QStringList PageManager::categories() const
{
    QStringList categories;
    return categories;
}


void PageManager::selectCategory( QString categoryId )
{

}


void PageManager::selectPage( QString pageId )
{

}



} }


