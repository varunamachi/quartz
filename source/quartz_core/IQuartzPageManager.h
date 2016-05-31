#pragma once

#include <QStringList>
#include <QWidget>

#include <vqcore/VQCommon.h>

#include "QuartzCore.h"


namespace Vq { namespace Quartz {

class QuartzPage : public QWidget
{
public:
    QuartzPage( const QString &pageId,
                const QString &category,
                const QString &categoryName,
                const QString &displayName,
                QWidget *parent = nullptr )
        : QWidget( parent )
        , m_pageId( pageId )
        , m_categoryId( category )
        , m_categoryName( categoryName )
        , m_displayName( displayName )
    {

    }

    const QString & pageId() const
    {
        return m_pageId;
    }

    const QString & pageCategoryId() const
    {
        return m_categoryId;
    }

    const QString & pageDisplayName() const
    {
        return m_displayName;
    }

    const QString & pageCategoryName() const
    {
        return m_categoryName;
    }

private:
    QString m_pageId;

    QString m_categoryId;

    QString m_categoryName;

    QString m_displayName;
};


VQ_INTERFACE IQuartzPageManager
{
    virtual void addPage( QuartzPage *page ) = 0;

    virtual void removePage( const QString &pageId ) = 0;

    virtual void removePage( QuartzPage *page ) = 0;

    virtual void removePageCategory( const QString &categoryId ) = 0;

    virtual QuartzPage * page( const QString &pageId ) const = 0;

    virtual QList< QuartzPage *> pages() const = 0;

    virtual QList< QuartzPage *> pages( const QString &categoryId ) const = 0;

    virtual QuartzPage * currentPage() const = 0;

    virtual const QString currentCategory() const = 0;

    virtual QStringList categories() const = 0;

    virtual void selectCategory( QString categoryId ) = 0;

    virtual void selectPage( QString pageId ) = 0;

    virtual ~IQuartzPageManager() { }

};


} }
