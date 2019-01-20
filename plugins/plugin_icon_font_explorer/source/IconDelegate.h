#pragma once

#include <QStyledItemDelegate>

namespace Quartz { namespace Ext { namespace IconFontExplorer {

class IconDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit IconDelegate(QObject *parent = nullptr);

    ~IconDelegate() override;

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:

};

} } }
