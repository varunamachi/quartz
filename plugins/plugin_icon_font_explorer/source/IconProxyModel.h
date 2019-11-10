#pragma once

#include <memory>

#include <QSortFilterProxyModel>

namespace Quartz {

enum class IconFontFamily : int;

namespace Ext { namespace IconFontExplorer {

class IconProxyModel : public QSortFilterProxyModel {
public:
    IconProxyModel(QObject* parent = nullptr);

    ~IconProxyModel() override;

public:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex& srcParent) const override;

public slots:
    void setExpression(const QString& expression);

    void setFont(const IconFontFamily& font);

protected:
    bool lessThan(const QModelIndex& left,
                  const QModelIndex& right) const override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Ext::IconFontExplorer
} // namespace Quartz
