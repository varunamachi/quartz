#pragma once

#include <QWidget>

#include <core/utils/Macros.h>

#include "QuartzItem.h"

namespace Quartz {


QZ_INTERFACE IQuartzTitleBar
{
    virtual void addItem( QuartzItem *widget ) = 0;

    virtual void removeItem( QuartzItem *widget ) = 0;

    virtual void removeItem( const QString &itemId ) = 0;

    virtual void removeCategory( const QString &category ) = 0;

    virtual QList< QuartzItem *> items() const = 0;

    virtual QList< QuartzItem *> items( const QString category ) = 0;
};

}
