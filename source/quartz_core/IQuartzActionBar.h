#pragma once

#include <QWidget>

#include <vqcore/VQCommon.h>

#include "QuartzItem.h"
#include "QuartzCore.h"

namespace Vam { namespace Quartz {

VQ_INTERFACE IQuartzActionBar
{
    virtual void addItem( QuartzItem *widget ) = 0;

    virtual void removeItem( QuartzItem *widget ) = 0;

    virtual void removeItem( const QString &itemId ) = 0;

    virtual void removeCategory( const QString &category ) = 0;

    virtual QList< QuartzItem *> items() const = 0;

    virtual QList< QuartzItem *> items( const QString category ) = 0;
};

} }
