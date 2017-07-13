

#include <QCheckBox>

#include "CheckBoxDeligate.h"

namespace Quartz { namespace Plugin { namespace Creator {

CheckBoxDelegate::CheckBoxDelegate( QWidget *parent )
    : QStyledItemDelegate{ parent }
{

}

CheckBoxDelegate::~CheckBoxDelegate()
{

}

void CheckBoxDelegate::paint( QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index ) const
{

}

QSize CheckBoxDelegate::sizeHint( const QStyleOptionViewItem &option,
                                  const QModelIndex &index ) const
{
    return QSize{ 24, 24 };
}

QWidget * CheckBoxDelegate::createEditor( QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index ) const
{
    //mpre need to be done
    return new QCheckBox{ parent };
}

void CheckBoxDelegate::setEditorData( QWidget *editor,
                                      const QModelIndex &index ) const
{

}

void CheckBoxDelegate::setModelData( QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index ) const
{

}

} } }
