
#include <QPainter>
#include <QCheckBox>
#include <QStyleOptionButton>
#include <QApplication>
#include <QObject>

#include "CheckBoxDeligate.h"

namespace Quartz {

CheckBoxDelegate::CheckBoxDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

CheckBoxDelegate::~CheckBoxDelegate()
{

}

void CheckBoxDelegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    if (index.data().canConvert<bool>()) {
        auto val = index.data().toBool();
        QStyleOptionButton checkbox;
        checkbox.state |= QStyle::State_Selected;
        checkbox.state |= val ? QStyle::State_On : QStyle::State_Off;
        checkbox.rect = QApplication::style()->subElementRect(
                    QStyle::SE_CheckBoxIndicator,
                    &checkbox,
                    nullptr);
        auto x = option.rect.center().x() - checkbox.rect.width() / 2 - 20;
        auto y = option.rect.center().y() - checkbox.rect.height() / 2;
        checkbox.rect.moveTo(x, y);
        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
        }
        QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                            &checkbox,
                                            painter);
    }
}

QSize CheckBoxDelegate::sizeHint(const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget * CheckBoxDelegate::createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &/*option*/,
        const QModelIndex &/*index*/) const
{
    auto checkbox = new QCheckBox(parent);
    checkbox->setStyleSheet(
        "QCheckBox {margin-left: 10%;}");
    return checkbox;
}

void CheckBoxDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    auto val = index.data().toBool();
    auto box = qobject_cast< QCheckBox *>(editor);
    box->setChecked(val);
}

void CheckBoxDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    auto box = qobject_cast< QCheckBox *>(editor);
    model->setData(index, box->isChecked());
}

}
