#pragma once

#include <QStyledItemDelegate>

namespace Quartz {

class EditorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EditorDelegate( QWidget *parent = nullptr );

    QWidget* createEditor( QWidget *parent,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index ) const override;

    void setEditorData( QWidget *editor,
                        const QModelIndex &index) const override;


    void setModelData( QWidget *editor,
                       QAbstractItemModel *model,
                       const QModelIndex &index ) const override;

private:


};

}
