#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include <core/ext/IExtensionAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class QzScroller;
class QuartzItem;
class AbstractActionItemProvider;

class QUARTZ_BASE_API ActionBar : public QWidget
                                , public Ext::IExtensionAdapter
{
    Q_OBJECT
public:
    explicit ActionBar(int height, QWidget *parent = nullptr);

    void addItem(QuartzItem *item);

    void removeItem(QuartzItem *item);

    void removeItem(const QString &item);

    QList< QuartzItem * > items() const;

    QList< QuartzItem * > items(const QString category);

    void removeCategory(const QString &category);

public:
    const QString & extensionType() const override;

    const QString & extensionAdapterName() const override;

    bool handleExtension(Ext::Extension *extension) override;

    bool finalizeExtension() override;

    const static QString ADAPTER_NAME;

private:
    int m_height;

    QzScroller *m_scroller;

    QHash< QString, QuartzItem *> m_items;

    QVector< QuartzItem *> m_extensionItems;

//    QVector< AbstractActionItemProvider *> m_itemProviders;

    // IExtensionAdapter interface

};


}
