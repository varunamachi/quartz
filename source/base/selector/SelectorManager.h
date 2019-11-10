#pragma once

#include <QWidget>

#include <core/ext/IExtensionAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class AbstractContainer;
class QzScroller;
class AbstractSelector;

class QUARTZ_BASE_API SelectorManager
    : public QWidget
    , public Ext::IExtensionAdapter {
    Q_OBJECT
public:
    explicit SelectorManager(AbstractContainer* container, QWidget* parent = 0);

    ~SelectorManager();

    void addSelector(AbstractSelector* selector);

    void removeSelector(const QString& selectorId);

    void removeSelector(AbstractSelector* selector);

    AbstractSelector* selector(const QString& selectorId) const;

    QList<AbstractSelector*> selectors() const;

    AbstractSelector* currentSelector() const;

    void selectSelector(QString selectorId);

public:
    const QString& extensionType() const override;

    const QString& extensionAdapterName() const override;

    bool handleExtension(Ext::Extension* ext) override;

    bool finalizeExtension() override;

    static const QString ADAPTER_NAME;

private Q_SLOTS:
    void onSelectorSelected(const QString& selectorId, QWidget* widget);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
