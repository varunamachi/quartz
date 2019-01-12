#pragma once

#include <QWidget>

#include "../QuartzBase.h"

#include <core/ext/IExtensionAdapter.h>

class QPushButton;

namespace Quartz {

class QuartzItem;
class QzScroller;

class QUARTZ_BASE_API TitleBar : public QWidget
                               , public Ext::IExtensionAdapter
{
    Q_OBJECT

public:
    explicit TitleBar(
            int height,
            bool showWindowControls,
            QWidget *parent = nullptr);

    void addItem(QuartzItem *item);

    void removeItem(QuartzItem *item);

    void removeItem(const QString &item);

    QList< QuartzItem * > items() const;

    QList< QuartzItem * > items(const QString category);

    void removeCategory(const QString &category);

public:
    const QString &extensionType() const override;

    const QString &extensionAdapterName() const override;

    bool handleExtension(Ext::Extension *ext) override;

    bool finalizeExtension() override;

    static const QString ADAPTER_NAME;

signals:
    void sigMinimizeRequested();

    void sigMaxRestoreRequested();

    void sigCloseRequested();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    int m_height;

    QHash< QString, QuartzItem *> m_items;

    QVector< QuartzItem *> m_extensionItems;

    QzScroller *m_scroller;

//    QPushButton *m_closeBtn;

//    QPushButton *m_maxRestoreBtn;

//    QPushButton *m_minimizeBtn;


};

}
