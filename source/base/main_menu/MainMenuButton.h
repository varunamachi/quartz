#pragma once

#include <QToolButton>

#include <core/ext/IExtensionAdapter.h>

#include "../QuartzBase.h"

class QAction;

namespace Quartz {

class QUARTZ_BASE_API MainMenuButton : public QToolButton
                                     , public Ext::IExtensionAdapter
{
    Q_OBJECT
public:
    explicit MainMenuButton(QWidget *parent = nullptr);

    ~MainMenuButton();

    void addAction(QAction *action);

    QAction * addMenu(QMenu *menu);

    static const QString ADAPTER_NAME;

public:
    // IExtensionAdapter interface
    const QString &extensionType() const;

    const QString &extensionAdapterName() const;

    bool handleExtension(Ext::Extension *extension);

    bool finalizeExtension();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
