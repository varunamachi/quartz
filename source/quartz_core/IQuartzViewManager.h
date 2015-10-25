#pragma once

#include <QWidget>
#include <QString>
#include <QStringList>

#include <vqcore/VQCommon.h>

#include "QuartzCore.h"


namespace Vam { namespace Quartz {

class QZ_CORE_EXPORT  QuartzView : public QWidget
{
public:
    QuartzView( const QString &viewId,
                const QStringList &categories,
                const QString &displayName,
                QWidget *parent = nullptr )
        : QWidget( parent )
        , m_viewId( viewId )
        , m_categories( categories )
        , m_displayName( displayName )
    {

    }

    const QString & viewId() const
    {
        return m_viewId;
    }

    const QStringList & viewCategories() const
    {
        return m_categories;
    }

    const QString & viewDisplayName() const
    {
        return m_displayName;
    }

private:

    QString m_viewId;

    QStringList m_categories;

    QString m_displayName;
};


VQ_INTERFACE IQuartzViewManager
{
    virtual void addView( QuartzView *view ) = 0;

    virtual void removeView( const QString &pageId ) = 0;

    virtual void removeView( QuartzView *view) = 0;

    virtual void removeViewCategory( const QString &categoryId ) = 0;

    virtual QuartzView * page( const QString &pageId ) = 0;

    virtual QList< QuartzView *> views( const QString &categoryId ) = 0;
};

} }
