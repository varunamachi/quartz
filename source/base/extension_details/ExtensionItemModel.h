#pragma once

#include <memory>

#include <QAbstractItemModel>

#include "../QuartzBase.h"

namespace Quartz { namespace Ext {

class Extension;

class QUARTZ_BASE_API ExtensionItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ExtensionItemModel(QObject *parent);

    ~ExtensionItemModel();

    QModelIndex index(int row,
                       int column,
                       const QModelIndex &parent) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool hasChildren(const QModelIndex &parent) const override;

    QVariant headerData(int section,
                         Qt::Orientation orientation,
                         int role) const override;

    void setExtensionList(
            const QVector<std::shared_ptr<Extension>> *exts);

    void clear();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} }
