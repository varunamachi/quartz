

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
}


void PageManager::removePage( const QString &pageId )
{
}


void PageManager::removePage( QuartzPage *page )
{
}


void PageManager::removePageCategory( const QString &categoryId )
{
}


QuartzPage * PageManager::page( const QString &pageId ) const
{
}


QList< QuartzPage * > PageManager::pages()
{
}


QList< QuartzPage * > PageManager::pages( const QString &categoryId ) const
{
}


QuartzPage * PageManager::currentPage() const
{
}


const QString & PageManager::currentCategory() const
{
}


QStringList PageManager::categories() const
{
}


PageManager::selectCategory( QString categoryId )
{
}


void PageManager::selectPage( QString pageId )
{
}



} }


