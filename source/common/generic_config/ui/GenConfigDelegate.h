#pragma once

#include <QStyledItemDelegate>

#include "../../QuartzCommon.h"

namespace Quartz {

class QUARTZ_COMMON_API GenConfigDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit GenConfigDelegate(QWidget* parent = nullptr);

    void updateEditorGeometry(QWidget* editor,
                              const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;

    QWidget* createEditor(QWidget* parent,
                          const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor,
                       const QModelIndex& index) const override;

    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override;
};

} // namespace Quartz
