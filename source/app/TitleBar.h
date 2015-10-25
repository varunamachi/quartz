#pragma once

#include <quartz_core/IQuartzTitleBar.h>

namespace Vam { namespace Quartz {

class TitleBar : public QWidget
               , public IQuartzTitleBar
{
    explicit TitleBar( int height, QWidget *parent = nullptr );

    // IQuartzTitleBar interface
public:
    void addItem(QuartzItem *widget);
    void removeItem(QuartzItem *widget);
    void removeItem(const QString &itemId);
    QList<QuartzItem *> items() const;
    QList<QuartzItem *> items(const QString category);
    void removeCategory(const QString &category);
};

} }
