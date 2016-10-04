#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include <core/extension_system/IPluginAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class QzScroller;
class QuartzItem;

class QUARTZ_BASE_API ActionBar : public QWidget
                                , public IPluginAdapter
{
    Q_OBJECT
public:
    explicit ActionBar( int height, QWidget *parent = nullptr );

    void addItem( QuartzItem *item );

    void removeItem( QuartzItem *item );

    void removeItem( const QString &item );

    QList< QuartzItem * > items() const;

    QList< QuartzItem * > items(const QString category);

    void removeCategory( const QString &category );

public:
    const QString & pluginType() const override;

    const QString & pluginAdapterName() const override;

    bool handlePlugin(IPlugin *plugin) override;

    bool finalizePlugins() override;

    const static QString PLUGIN_TYPE;

    const static QString ADAPTER_NAME;

private:
    int m_height;

    QzScroller *m_scroller;

    QHash< QString, QuartzItem *> m_items;

    // IPluginAdapter interface

};


}
