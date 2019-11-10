
#include <QLineEdit>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>
#include <QPainter>
#include <QApplication>
#include <QSpinBox>
#include <QSignalBlocker>
#include <QCheckBox>

#include "../../model_view/TreeNode.h"
#include "../model/Param.h"
#include "../model/BooleanParam.h"
#include "../model/TextParam.h"
#include "../model/RangeParam.h"
#include "../model/ChoiceParam.h"
#include "GenConfigDelegate.h"

namespace Quartz {

GenConfigDelegate::GenConfigDelegate(QWidget* parent)
    : QStyledItemDelegate(parent) {
}

QWidget* GenConfigDelegate::createEditor(QWidget* parent,
                                         const QStyleOptionViewItem& /*option*/,
                                         const QModelIndex& index) const {
    QWidget* widget = new QLineEdit(parent);
    auto node = index.data(Qt::UserRole).value<TreeNode*>();
    auto param = dynamic_cast<Param*>(node);
    if (param != nullptr) {
        switch (param->type()) {
        case ParamType::Text: {
            auto le = new QLineEdit(parent);
            widget = le;
            connect(le, &QLineEdit::textEdited, [le, this]() {
                // I know, const_cast is bad...
                emit const_cast<GenConfigDelegate*>(this)->commitData(le);
            });
        } break;
        case ParamType::Range: {
            auto sl = new QSpinBox(parent);
            widget = sl;
            connect(sl, &QSpinBox::editingFinished, [sl, this]() {
                // I know, const_cast is bad...
                emit const_cast<GenConfigDelegate*>(this)->commitData(sl);
            });
        } break;
        case ParamType::Choice: {
            auto combo = new QComboBox(parent);
            widget = combo;
            connect(combo,
                    qOverload<int>(&QComboBox::currentIndexChanged),
                    [combo, this]() {
                        // I know, const_cast is bad...
                        emit const_cast<GenConfigDelegate*>(this)->commitData(
                            combo);
                    });
        } break;
        case ParamType::Boolean: {
            auto checkbox = new QCheckBox(parent);
            connect(checkbox, &QCheckBox::stateChanged, [checkbox, this]() {
                // I know, const_cast is bad...
                emit const_cast<GenConfigDelegate*>(this)->commitData(checkbox);
            });
            widget = checkbox;
        } break;
        case ParamType::Fixed: // no edit for fixed
            break;
        }
    }
    return widget;
}

void GenConfigDelegate::setEditorData(QWidget* editor,
                                      const QModelIndex& index) const {
    auto node = treenode_cast<Param*>(index.data(Qt::UserRole));
    if (node != nullptr) {
        switch (node->type()) {
        case ParamType::Boolean: {
            //            QStyledItemDelegate::setEditorData(editor, index);
            auto bparam = static_cast<BooleanParam*>(node);
            auto cb = static_cast<QCheckBox*>(editor);
            cb->setChecked(bparam->value().toBool());
        } break;
        case ParamType::Text: {
            auto tparam = static_cast<TextParam*>(node);
            auto le = static_cast<QLineEdit*>(editor);
            le->setText(tparam->value().toString());
        } break;
        case ParamType::Range: {
            auto rparam = static_cast<RangeParam*>(node);
            auto sl = static_cast<QSpinBox*>(editor);
            sl->setValue(rparam->value().toInt());
        } break;
        case ParamType::Choice: {
            auto cparam = static_cast<ChoiceParam*>(node);
            auto combo = static_cast<QComboBox*>(editor);
            for (auto i = 0; i < cparam->numOption(); ++i) {
                auto opt = cparam->option(i);
                combo->addItem(opt.first, opt.second);
            }
            if (cparam->numOption() > 0) {
                combo->setCurrentIndex(cparam->index());
            }
            //            combo->showPopup();
        } break;
        case ParamType::Fixed: // no edit for fixed
            break;
        }
    }
}

void GenConfigDelegate::setModelData(QWidget* editor,
                                     QAbstractItemModel* model,
                                     const QModelIndex& index) const {
    auto node = treenode_cast<Param*>(index.data(Qt::UserRole));
    if (node != nullptr) {
        QVariant data;
        switch (node->type()) {
        case ParamType::Boolean: {
            auto cb = static_cast<QCheckBox*>(editor);
            data = cb->checkState();
            return; //?
        }
        case ParamType::Text: {
            auto le = static_cast<QLineEdit*>(editor);
            data = le->text();
        } break;
        case ParamType::Range: {
            auto sl = static_cast<QSpinBox*>(editor);
            data = sl->value();
        } break;
        case ParamType::Choice: {
            auto combo = static_cast<QComboBox*>(editor);
            data = combo->currentData();
        } break;
        case ParamType::Fixed: // no edit for fixed
            data = node->value();
            break;
        }
        model->setData(index, data);
    }
}

void GenConfigDelegate::updateEditorGeometry(
    QWidget* editor,
    const QStyleOptionViewItem& option,
    const QModelIndex& /*index*/) const {
    editor->setGeometry(option.rect);
}

} // namespace Quartz
