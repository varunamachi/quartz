#include <QPainter>

#include <common/model_view/TreeNode.h>
#include <common/iconstore/Icons.h>

#include "IconNode.h"
#include "IconDelegate.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

IconDelegate::IconDelegate(QObject *parent)
    :QStyledItemDelegate (parent)
{

}

IconDelegate::~IconDelegate()
{

}

void IconDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    auto iconNode = treenode_cast<IconNode *>(index.data(Qt::UserRole));
    if (iconNode != nullptr) {
        auto icon = getIcon(iconNode->iconInfo());
        icon.paint(painter, option.rect);
    }
}

QSize IconDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    return {64, 64};
}


} } }
