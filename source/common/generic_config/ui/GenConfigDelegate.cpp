
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
#include "ParamTreeNode.h"

namespace Quartz {

GenConfigDelegate::GenConfigDelegate( QWidget *parent )
    : QStyledItemDelegate{ parent }
{

}

//void GenConfigDelegate::paint(
//        QPainter *painter,
//        const QStyleOptionViewItem &option,
//        const QModelIndex &index ) const
//{
////    QStyledItemDelegate::paint( painter, option, index );
//    auto node = dynamic_cast< ParamTreeNode *>(
//                static_cast< TreeNode *>( index.internalPointer() ));
//    if( node != nullptr ) {
//        switch ( node->param()->type() ) {
//        case ParamType::Boolean: {
//            auto val = index.data().toBool();
//            QStyleOptionButton checkbox;
//            checkbox.state |= QStyle::State_Selected;
//            checkbox.state |= val ? QStyle::State_On : QStyle::State_Off;
//            checkbox.rect = QApplication::style()->subElementRect(
//                        QStyle::SE_CheckBoxIndicator,
//                        &checkbox,
//                        nullptr );
//            auto x = option.rect.center().x() - checkbox.rect.width() / 2 - 20;
//            auto y = option.rect.center().y() - checkbox.rect.height() / 2;
//            checkbox.rect.moveTo( x, y );
//            if( option.state & QStyle::State_Selected ) {
//                painter->fillRect( option.rect, option.palette.highlight() );
//            }
//            QApplication::style()->drawControl( QStyle::CE_CheckBox,
//                                                &checkbox,
//                                                painter );
//        }
//            break;
//        case ParamType::Range:
//        case ParamType::Text:
//        case ParamType::Choice:
//            QStyledItemDelegate::paint( painter, option, index );
//            break;
//        }
//    }
//}

QWidget* GenConfigDelegate::createEditor(
        QWidget* parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index ) const
{
    QWidget *widget = new QLineEdit{ parent };
    auto node = dynamic_cast< ParamTreeNode *>(
                static_cast< TreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        switch( node->param()->type() ) {
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
    auto node = dynamic_cast< ParamTreeNode *>(
                static_cast< TreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        switch( node->param()->type() ) {
        case ParamType::Boolean: {
            QStyledItemDelegate::setEditorData( editor, index );
            auto combo = qobject_cast< QComboBox *>( editor );
            if( combo != nullptr ) {
                combo->showPopup();
            }
        }
            break;
        case ParamType::Text: {
            auto tparam = static_cast< TextParam *> ( node->param() );
            auto le = static_cast< QLineEdit *>( editor );
            le->setText( tparam->value().toString() );
        }
            break;
        case ParamType::Range: {
            auto rparam = static_cast< RangeParam *> ( node->param() );
            auto sl = static_cast< QSpinBox *>( editor );
            sl->setValue( rparam->value().toInt() );
        }
            break;
        case ParamType::Choice: {
            auto cparam = static_cast< ChoiceParam *> ( node->param() );
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
    auto node = dynamic_cast< ParamTreeNode *>(
                static_cast< TreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        QVariant data;
        switch( node->param()->type() ) {
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
        node->param()->setValue( data );
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
