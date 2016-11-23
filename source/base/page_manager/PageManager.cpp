
#include <core/logger/Logging.h>

#include <common/widgets/QzScroller.h>
#include <common/widgets/StackedContainer.h>


#include "QuartzPage.h"
#include "AbstractPageProvider.h"
#include "PageManager.h"

namespace Quartz {

const QString PageManager::ADAPTER_NAME{ "page_manager" };

PageManager::PageManager( int categoryWidth,
                          int pagerHeight,
                          QWidget *parent )
    : QWidget( parent )
    , m_selectorWidth( categoryWidth )
    , m_holderHeight( pagerHeight )
    , m_catContainer( new StackedContainer(
                          categoryWidth,
                          40,
                          AbstractContainer::SelectorPosition::Before,
                          Qt::Vertical,
                          Qt::Horizontal,
                          this ))
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget( m_catContainer );
    layout->setContentsMargins( QMargins() );
    this->setLayout( layout );

}


void PageManager::addPage( QuartzPage *page )
{
    if( page != nullptr ) {
        AbstractContainer *container = m_pageContainers.value(
                    page->pageCategoryId() );
        if( container == nullptr ) {
            container = new StackedContainer(
                        m_holderHeight,
                        150,
                        AbstractContainer::SelectorPosition::Before,
                        Qt::Horizontal,
                        Qt::Horizontal,
                        this );
            m_catContainer->addWidget( page->pageCategoryId(),
                                       page->pageCategoryName(),
                                       container );
            m_pageContainers.insert( page->pageCategoryId(), container );
        }
        container->addWidget( page->pageId(),
                              page->pageDisplayName(),
                              page );
        m_pages.insert( page->pageId(), page );
    }
    else {
        QZ_ERROR( "Qz:PageManager" ) << "Invalid page given";
    }
}


void PageManager::removePage( const QString &pageId )
{
    QuartzPage *page = m_pages.value( pageId );
    if( page != nullptr ) {
        removePage( pageId );
    }
    else {
        QZ_ERROR( "QzApp:PageMan" )
                << "Could not remove page with id "
                << pageId << ". No page with given ID found";
    }
}


void PageManager::removePage( QuartzPage *page )
{
    if( page != nullptr ) {
        AbstractContainer *container =
                m_pageContainers.value( page->pageCategoryId() );
        if( container ) {
            container->removeWidget( page->pageId() );
            m_pages.remove( page->pageId() );
            if( container->isEmpty() ) {
                QZ_INFO( "Qz:PageManager" )
                        << "There are no pages left in the category with "
                           "id " << page->pageCategoryId()
                        << ". The container for this category will be "
                           "removed";
                m_pageContainers.remove( page->pageCategoryId() );
                delete container;
            }
        }
        else {
            QZ_ERROR( "Qz:PageManager" )
                    << "Could not remove page with ID " << page->pageId()
                    << ". Could not find the category of the page - "
                    << page->pageCategoryId();

        }
        QZ_INFO( "Qz:PageManager" )
                << "succesfully added  Page with id " << page->pageId()
                << " of category " << page->pageCategoryId();
    }
    else {
        QZ_ERROR( "Qz:PageManager" )
                << "Could not remove page with id Invalid page given";
    }
}


void PageManager::removePageCategory( const QString &categoryId )
{
    AbstractContainer *container = m_pageContainers.value( categoryId );
    if( container != nullptr ) {
        QList< QString > allIds = container->allIds();
        for( const QString &id : allIds ) {
            m_pages.remove( id );
        }
        m_pageContainers.remove( categoryId );
        delete container;
    }
    else {
        QZ_ERROR( "Qz:PageManager" )
                << "Could not remove category " << categoryId
                << ". No such category found";
    }
}


QuartzPage * PageManager::page( const QString &pageId ) const
{
    QuartzPage *page = m_pages.value( pageId );
    return page;
}


QList< QuartzPage * > PageManager::pages() const
{
    QList< QuartzPage *> pages;
    auto it = m_pages.begin();
    for( ; it != m_pages.end(); ++ it ) {
        pages.append( it.value() );
    }
    return pages;
}


QList< QuartzPage * > PageManager::pages( const QString &categoryId ) const
{
    QList< QuartzPage *> pages;
    for( auto it = m_pages.begin(); it != m_pages.end(); ++ it ) {
        QuartzPage *page = it.value();
        if( page->pageCategoryId() == categoryId ) {
            pages.append( page );
        }
    }
    return pages;
}


QuartzPage * PageManager::currentPage() const
{
    QuartzPage *page = nullptr;
    QString curCategory = m_catContainer->currentId();
    if( ! curCategory.isEmpty() ) {
        AbstractContainer *pageContnr = m_pageContainers.value( curCategory );
        if( pageContnr != nullptr ) {
            QString curPageId = pageContnr->currentId();
            QWidget *widget = pageContnr->widget( curPageId );
            page = dynamic_cast< QuartzPage *>( widget );
        }
        else {
            QZ_ERROR( "Qz:PageManager" )
                    << "Could not retrieve current page, there are no "
                       "pages in the current category"
                    << curCategory;
        }
    }
    else {
        QZ_ERROR( "Qz:PageManager" )
                << "Could not retrieve current page There are no categories "
                   "registered" << curCategory;
    }
    return page;
}


const QString PageManager::currentCategory() const
{
    QString curCategory = m_catContainer->currentId();
    return curCategory;
}


QStringList PageManager::categories() const
{
    QStringList categoies;
    auto it = m_pageContainers.begin();
    for( ; it != m_pageContainers.end(); ++ it ) {
        categoies.append( it.key() );
    }
    return categoies;
}


void PageManager::selectCategory( QString categoryId )
{
    m_catContainer->select( categoryId );
}


void PageManager::selectPage( QString pageId )
{
    bool result = false;
    QuartzPage *page = m_pages.value( pageId );
    if( page != nullptr ) {
        selectCategory( page->pageCategoryId() );
        AbstractContainer *pageCont = m_pageContainers.value(
                    page->pageCategoryId() );
        if( pageCont ) {
            pageCont->select( pageId );
            result = true;
        }
    }
    if( ! result ){
        QZ_ERROR( "Qz:PageManager" )
                << "Could not find a page with id " << pageId;
    }
}

const QString & PageManager::pluginType() const
{
    return AbstractPageProvider::PLUGIN_TYPE;
}

const QString & PageManager::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool PageManager::handlePlugin( AbstractPlugin *plugin )
{
    auto result = false;
    auto provider = dynamic_cast< AbstractPageProvider *>( plugin );
    if( provider != nullptr ) {
        auto pages = provider->pages();
        foreach( auto page, pages ) {
            addPage( page );
            m_pluginPages.push_back( page );
        }
        result = true;
    }
    else {
        auto pluginName = plugin != nullptr ? plugin->pluginId()
                                            : "<null>";
        QZ_ERROR( "Qz:PageManager" )
                << "Invalid page plugin provided: " << pluginName;
    }
    return result;
}

bool PageManager::finalizePlugins()
{
//    for( int i = 0; i < m_pluginPages.size(); ++ i ) {
//        auto page = m_pluginPages.at( i );
//        removePage( page );
//    }
    m_pluginPages.clear();
    return true;
}

}


