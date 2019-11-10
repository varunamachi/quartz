#pragma once

#include <memory>
#include <functional>

#include <QTreeView>

#include "../QuartzCommon.h"

class QAction;
class QModelIndex;

namespace Quartz {

struct ContextMenuItem {
    QString m_name;

    std::function<void(QModelIndex)> m_func;
};

class QUARTZ_COMMON_API QzTreeView : public QTreeView {
    Q_OBJECT

public:
    QzTreeView(QWidget* parent = nullptr);

    ~QzTreeView();

    void mousePressEvent(QMouseEvent* event) override;

    void addContextAction(ContextMenuItem cm);

    void removeContextMenu(const QString& name);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
