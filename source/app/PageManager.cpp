

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


