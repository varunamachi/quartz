

#include "TreeNode.h"
#include "BasicSortFilter.h"

namespace Quartz {

struct BasicSortFilter::Data {
    QString m_expression;
};

BasicSortFilter::BasicSortFilter(QObject* parent)
    : QSortFilterProxyModel(parent)
    , m_data{new Data{}} {
}

BasicSortFilter::~BasicSortFilter() {
}

bool BasicSortFilter::filterAcceptsRow(int sourceRow,
                                       const QModelIndex& srcParent) const {
    auto accept = false;
    auto index = sourceModel()->index(sourceRow, 0, srcParent);
    auto node = static_cast<TreeNode*>(index.internalPointer());
    if (node != nullptr) {
        for (auto i = 0; i < node->numFields(); ++i) {
            const auto str = node->fieldValue(i).toString();
            accept = str.contains(m_data->m_expression, Qt::CaseInsensitive);
            if (accept) {
                break;
            }
        }
    }
    return accept;
}

void BasicSortFilter::setExpression(const QString& expression) {
    m_data->m_expression = expression;
    this->invalidate();
}

bool BasicSortFilter::lessThan(const QModelIndex& left,
                               const QModelIndex& right) const {
    QVariant lData = left.data();
    QVariant rData = right.data();
    bool ok;
    int leftInt = lData.toInt(&ok);
    int rightInt = rData.toInt(&ok);
    if (ok) {
        return leftInt < rightInt;
    }
    return QString::localeAwareCompare(lData.toString(), rData.toString()) < 0;
}

} // namespace Quartz
