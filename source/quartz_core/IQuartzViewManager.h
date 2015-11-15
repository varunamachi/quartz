#pragma once

#include <QWidget>
#include <QString>
#include <QStringList>

#include <vqcore/VQCommon.h>

#include "QuartzCore.h"


namespace Vam { namespace Quartz {

class QuartzView : public QWidget
{
public:
    QuartzView( const QString &viewId,
                const QString &category,
                const QString &displayName,
                QWidget *parent = nullptr )
        : QWidget( parent )
        , m_viewId( viewId )
        , m_categoryId( category )
        , m_displayName( displayName )
    {

    }

    const QString & viewId() const
    {
        return m_viewId;
    }

    const QString & viewCategoryId() const
    {
        return m_categoryId;
    }

    const QString & viewDisplayName() const
    {
        return m_displayName;
    }

    const QString & viewCategoryName() const
    {
        return m_categoryName;
    }

private:
    QString m_viewId;

    QString m_categoryId;

    QString m_categoryName;

    QString m_displayName;
};


VQ_INTERFACE IQuartzViewManager
{
    virtual void addView( QuartzView *view ) = 0;

    virtual void removeView( const QString &viewId ) = 0;

    virtual void removeView( QuartzView *view) = 0;

    virtual void removeCategory( const QString &categoryId );

    virtual QuartzView * view( const QString &viewId ) const = 0;

    virtual QList< QuartzView *> views() const = 0;

    virtual QuartzView * currentView() const = 0;

    virtual void selectView( QString viewId ) = 0;
};

} }
