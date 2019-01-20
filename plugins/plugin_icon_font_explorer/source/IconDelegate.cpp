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
    auto iconNode = treenode_cast<IconNode *>(index.data(Qt::UserRole));
    if (iconNode != nullptr) {
        if (option.state & QStyle::State_Selected) {
            // Whitee pen while selection
            painter->fillRect(
                        option.rect,
                        QBrush{option.palette.color(QPalette::Highlight)});
        }
        auto icon = getIcon(iconNode->iconInfo());
        icon.paint(painter, QRect(
                       option.rect.left() + 10,
                       option.rect.top() + 10,
                       option.rect.width() - 20,
                       option.rect.height() - 20));
    }
}

QSize IconDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    return {64, 80};
}


} } }
