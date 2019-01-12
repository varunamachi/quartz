#pragma once

#include <QStyledItemDelegate>

#include "../QuartzCommon.h"

namespace Quartz {

class QUARTZ_COMMON_API EditorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EditorDelegate(QWidget *parent = nullptr);

    QWidget* createEditor(QWidget *parent,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                        const QModelIndex &index) const override;


    void setModelData(QWidget *editor,
                       QAbstractItemModel *model,
                       const QModelIndex &index) const override;

private:


};

}
