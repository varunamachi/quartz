#pragma once

#include <QAbstractItemModel>
#include <QIcon>

#include <core/ext/IExtensionAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class Node;
using NodePtr = std::shared_ptr<Node>;

class QUARTZ_BASE_API TreeModel
    : public QAbstractItemModel

{
    Q_OBJECT

public:
    TreeModel(QObject* parent = 0);

    ~TreeModel();

    const Node* node(const QStringList& path) const;

    static const QString ADAPTER_NAME;

public:
    QModelIndex index(int row,
                      int column,
                      const QModelIndex& parent) const override;

    QModelIndex parent(const QModelIndex& child) const override;

    int rowCount(const QModelIndex& parent) const override;

    int columnCount(const QModelIndex& parent) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    bool hasChildren(const QModelIndex& parent) const override;

public Q_SLOTS:
    Node* addNode(const QStringList& parentPath,
                  const QString& nodeName,
                  const QString& nodeId = QString(),
                  QIcon icon = QIcon());

    bool removeNode(const QStringList& path);

    bool selectNode(const QStringList& path) const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;

    bool addNode(const QStringList& parentPath, const NodePtr node);

    Node* traverse(Node* node,
                   const QStringList& path,
                   bool tillParent,
                   int depth) const;

    Node* createPath(Node* node, const QStringList& path, int depth);
};

} // namespace Quartz
