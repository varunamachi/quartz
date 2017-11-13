
#include <QLineEdit>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>
#include <QPainter>
#include <QApplication>
#include <QSpinBox>

#include "../../model_view/TreeNode.h"
#include "../model/Param.h"
#include "../model/BooleanParam.h"
#include "../model/TextParam.h"
#include "../model/RangeParam.h"
#include "../model/ChoiceParam.h"
#include "GenConfigDelegate.h"

namespace Quartz {

GenConfigDelegate::GenConfigDelegate( QWidget *parent )
    : QStyledItemDelegate{ parent }
{

}

QWidget* GenConfigDelegate::createEditor(
        QWidget* parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index ) const
{
    QWidget *widget = new QLineEdit{ parent };
    auto node = dynamic_cast< Param *>(
                static_cast< TreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        switch( node->type() ) {
        case ParamType::Boolean: {
//            auto cb = new QCheckBox{ parent };
//            cb->setGeometry( option.rect );
//            widget = cb;
            widget = QStyledItemDelegate::createEditor( parent, option, index );
        }
            break;
        case ParamType::Text: {
            auto le = new QLineEdit{ parent };
            widget = le;
        }
            break;
        case ParamType::Range: {
            auto sl = new QSpinBox{ parent };
            widget = sl;
        }
            break;
        case ParamType::Choice: {
            auto combo = new QComboBox{ parent };
            widget = combo;
        }
            break;
        }
    }
    return widget;
}

void GenConfigDelegate::setEditorData( QWidget *editor,
                                       const QModelIndex &index) const
{
    auto node = dynamic_cast< Param *>(
                static_cast< TreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        switch( node->type() ) {
        case ParamType::Boolean: {
            QStyledItemDelegate::setEditorData( editor, index );
            auto combo = qobject_cast< QComboBox *>( editor );
            if( combo != nullptr ) {
                combo->showPopup();
            }
        }
            break;
        case ParamType::Text: {
            auto tparam = static_cast< TextParam *> ( node );
            auto le = static_cast< QLineEdit *>( editor );
            le->setText( tparam->value().toString() );
        }
            break;
        case ParamType::Range: {
            auto rparam = static_cast< RangeParam *> ( node );
            auto sl = static_cast< QSpinBox *>( editor );
            sl->setValue( rparam->value().toInt() );
        }
            break;
        case ParamType::Choice: {
            auto cparam = static_cast< ChoiceParam *> ( node );
            auto combo = static_cast< QComboBox *>( editor );
            for( auto i = 0; i < cparam->numOption(); ++ i ) {
                auto opt = cparam->option( i );
                combo->addItem( opt.first, opt.second );
            }
            if( cparam->numOption() > 0 ) {
                combo->setCurrentIndex( cparam->index() );
            }
            combo->showPopup();
        }
            break;
        }
    }
}


void GenConfigDelegate::setModelData( QWidget *editor,
                                      QAbstractItemModel *model,
                                      const  QModelIndex &index ) const
{
    auto node = dynamic_cast< Param *>(
                static_cast< TreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        QVariant data;
        switch( node->type() ) {
        case ParamType::Boolean: {
            QStyledItemDelegate::setModelData( editor, model, index );
        }
            break;
        case ParamType::Text: {
            auto le = static_cast< QLineEdit *>( editor );
            data = le->text();
        }
            break;
        case ParamType::Range: {
            auto sl = static_cast< QSpinBox *>( editor );
            data = sl->value();
        }
            break;
        case ParamType::Choice: {
            auto combo = static_cast< QComboBox *>( editor );
            data = combo->currentIndex();
        }
            break;
        }
        node->setValue( data );
    }
}

void GenConfigDelegate::updateEditorGeometry(
        QWidget *editor,
        const QStyleOptionViewItem &option,
        const QModelIndex &/*index*/ ) const
{
    editor->setGeometry( option.rect );
}

}
