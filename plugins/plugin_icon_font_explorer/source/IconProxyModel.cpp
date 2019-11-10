
#include <common/iconstore/Icons.h>

#include "IconNode.h"
#include "IconProxyModel.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

struct IconProxyModel::Data {
    QString m_expression;

    IconFontFamily m_font = IconFontFamily::Any;
};

IconProxyModel::IconProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
    , m_data(std::make_unique<Data>()) {
}

IconProxyModel::~IconProxyModel() {
}

bool IconProxyModel::filterAcceptsRow(int sourceRow,
                                      const QModelIndex& srcParent) const {
    auto accept = false;
    auto index = sourceModel()->index(sourceRow, 0, srcParent);
    auto node = static_cast<IconNode*>(index.internalPointer());
    if (node != nullptr) {
        auto info = node->iconInfo();
        if (m_data->m_font == IconFontFamily::Any) {
            accept = info->m_name.contains(m_data->m_expression,
                                           Qt::CaseInsensitive)
                || info->m_fontName.contains(m_data->m_expression,
                                             Qt::CaseInsensitive);
        } else {
            accept = info->m_font == m_data->m_font
                && info->m_name.contains(m_data->m_expression,
                                         Qt::CaseInsensitive);
        }
    }
    return accept;
}

void IconProxyModel::setExpression(const QString& expression) {
    m_data->m_expression = expression;
    this->invalidate();
}

void IconProxyModel::setFont(const IconFontFamily& font) {
    m_data->m_font = font;
    this->invalidate();
}

bool IconProxyModel::lessThan(const QModelIndex& left,
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

}}} // namespace Quartz::Ext::IconFontExplorer
