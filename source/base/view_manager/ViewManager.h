#pragma once

#include <QWidget>
#include <QWidget>
#include <QHash>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QVBoxLayout>

#include <core/ext/IExtensionAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzView;
class AbstractContainer;
class QzScroller;

class QUARTZ_BASE_API ViewManager : public QWidget
                                  , public Ext::IExtensionAdapter
{
    Q_OBJECT
public:
    explicit ViewManager(AbstractContainer *container,
                          QWidget *parent = nullptr);

    ~ViewManager() override;

    void addView(QuartzView *view);

    void removeView(const QString &viewId);

    void removeView(QuartzView *view);

    void removeViewCategory(const QString &categoryId);

    QuartzView * view(const QString &viewId) const;

    QList< QuartzView *> views() const;

    QList< QuartzView *> views(const QString &categoryId) const;

    QuartzView * currentView() const;

    const QString currentCategory() const;

    QList<QString> categories() const;

    void selectView(QString viewId);

    template<typename T>
    T *view(const QString &viewId) const
    {
        return dynamic_cast<T *>(view(viewId));
    }

public:
    const QString & extensionType() const override;

    const QString & extensionAdapterName() const override;

    bool handleExtension(Ext::Extension *extension) override;

    bool finalizeExtension() override;

    static const QString ADAPTER_NAME;

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

}
