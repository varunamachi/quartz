
#include <QLineEdit>

#include "EditorDelegate.h"

namespace Quartz {

EditorDelegate::EditorDelegate(QWidget* parent)
    : QStyledItemDelegate(parent) {
}

QWidget* EditorDelegate::createEditor(QWidget* parent,
                                      const QStyleOptionViewItem& /*option*/,
                                      const QModelIndex& /*index*/) const {
    return new QLineEdit(parent);
}

void EditorDelegate::setEditorData(QWidget* editor,
                                   const QModelIndex& index) const {
    auto txt = qobject_cast<QLineEdit*>(editor);
    if (txt != nullptr) {
        txt->setText(index.data().toString());
    }
}

void EditorDelegate::setModelData(QWidget* editor,
                                  QAbstractItemModel* model,
                                  const QModelIndex& index) const {
    auto txt = qobject_cast<QLineEdit*>(editor);
    if (txt != nullptr) {
        model->setData(index, txt->text());
    }
}

} // namespace Quartz
