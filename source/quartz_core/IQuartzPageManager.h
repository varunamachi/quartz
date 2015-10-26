#pragma once

#include <QStringList>
#include <QWidget>

#include <vqcore/VQCommon.h>

#include "QuartzCore.h"


namespace Vam { namespace Quartz {

class QuartzPage : public QWidget
{
public:
    QuartzPage( const QString &pageId,
                const QString &categories,
                const QString &displayName,
                QWidget *parent = nullptr )
        : QWidget( parent )
        , m_pageId( pageId )
        , m_categories( categories )
        , m_displayName( displayName )
    {

    }

    const QString & pageId() const
    {
        return m_pageId;
    }

    const QStringList & pageCategories() const
    {
        return m_categories;
    }

    const QString & pageDisplayName() const
    {
        return m_displayName;
    }

private:

    QString m_pageId;

    QStringList m_categories;

    QString m_displayName;
};


VQ_INTERFACE QZ_CORE_EXPORT IQuartzPageManager
{
    virtual void addPage( QuartzPage *page ) = 0;

    virtual void removePage( const QString &pageId ) = 0;

    virtual void removePage( QuartzPage *page ) = 0;

    virtual void removePageCategory( const QString &categoryId ) = 0;

    virtual QuartzPage * page( const QString &pageId ) = 0;

    virtual QList< QuartzPage *> pages( const QString &categoryId ) = 0;
};


} }
