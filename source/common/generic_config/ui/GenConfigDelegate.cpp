
#include <QLineEdit>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>

#include "../../model_view/ITreeNode.h"
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

QWidget* GenConfigDelegate::createEditor( QWidget* parent,
                                          const QStyleOptionViewItem &/*option*/,
                                          const QModelIndex &index ) const
{
    QWidget *widget = nullptr;
    auto node = dynamic_cast< ParamTreeNode *>(
                static_cast< ITreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        switch( node->param()->type() ) {
        case ParamType::Boolean: {
            auto cb = new QCheckBox{ parent };
            widget = cb;
        }
            break;
        case ParamType::Text: {
            auto le = new QLineEdit{ parent };
            widget = le;
        }
            break;
        case ParamType::Range: {
            auto rparam = static_cast< RangeParam *> ( node->param() );
            auto sl = new QSlider{ parent };
            sl->setMaximum( rparam->maxVal() );
            sl->setMinimum( rparam->minVal() );
            widget = sl;
        }
            break;
        case ParamType::Choice: {
            auto cparam = static_cast< ChoiceParam *> ( node->param() );
            auto combo = new QComboBox{ parent };
            for( auto i = 0; i < cparam->numOption(); ++ i ) {
                auto opt = cparam->option( i );
                combo->addItem( opt.first, opt.second );
            }
        }
            break;
        }
    }
    return new QLineEdit{ parent };
}

void GenConfigDelegate::setEditorData( QWidget *editor,
                                       const QModelIndex &index) const
{
    auto node = dynamic_cast< ParamTreeNode *>(
                static_cast< ITreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        switch( node->param()->type() ) {
        case ParamType::Boolean: {
            auto bparam = static_cast< BooleanParam *> ( node->param() );
            auto cb = static_cast< QCheckBox *>( editor );
            cb->setChecked( bparam->value().toBool() );
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
            auto sl = static_cast< QSlider *>( editor );
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
            combo->setCurrentIndex( cparam->value().toInt() );
        }
            break;
        }
    }
}


void GenConfigDelegate::setModelData( QWidget *editor,
                                      QAbstractItemModel */*model*/,
                                      const  QModelIndex &index ) const
{
    auto node = dynamic_cast< ParamTreeNode *>(
                static_cast< ITreeNode *>( index.internalPointer() ));
    if( node != nullptr ) {
        QVariant data;
        switch( node->param()->type() ) {
        case ParamType::Boolean: {
            auto cb = static_cast< QCheckBox *>( editor );
            data = cb->isChecked();
        }
            break;
        case ParamType::Text: {
            auto le = static_cast< QLineEdit *>( editor );
            data = le->text();
        }
            break;
        case ParamType::Range: {
            auto sl = static_cast< QSlider *>( editor );
            data = sl->value();
        }
            break;
        case ParamType::Choice: {
            auto combo = static_cast< QComboBox *>( editor );
            data = combo->currentData();
        }
            break;
        }
        node->param()->setValue( data );
    }
}

}
