#pragma once

#include <QWidget>

#include <core/extension_system/IPluginAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class AbstractContainer;
class QzScroller;
class AbstractSelector;

class QUARTZ_BASE_API SelectorManager : public QWidget
                                      , public IPluginAdapter
{
    Q_OBJECT
public:
    explicit SelectorManager( AbstractContainer *container,
                              QWidget *parent = 0 );

    ~SelectorManager();

    void addSelector( AbstractSelector *selector );

    void removeSelector( const QString &selectorId );

    void removeSelector( AbstractSelector *selector );

    AbstractSelector * selector( const QString &selectorId ) const;

    QList< AbstractSelector *> selectors() const;

    AbstractSelector * currentSelector() const;

    void selectSelector( QString selectorId );

public:
    const QString & pluginType() const;

    const QString & pluginAdapterName() const;

    bool handlePlugin( AbstractPlugin *plugin );

    bool finalizePlugins();

    static const QString ADAPTER_NAME;

private Q_SLOTS:
    void onSelectorSelected( const QString &selectorId,
                             QWidget *widget );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
