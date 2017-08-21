#pragma once

#include <QStyledItemDelegate>

namespace Quartz {

class GenConfigDelegate : public QStyledItemDelegate
{
    explicit GenConfigDelegate( QWidget *parent = nullptr );

    QWidget* createEditor( QWidget *parent,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index ) const override;

    void setEditorData( QWidget *editor,
                        const QModelIndex &index) const override;


    void setModelData( QWidget *editor,
                       QAbstractItemModel *model,
                       const QModelIndex &index ) const override;
};

}
