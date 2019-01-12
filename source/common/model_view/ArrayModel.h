#pragma once

#include <memory>

#include "../QuartzCommon.h"
#include "AbstractTreeModel.h"

namespace Quartz {

class QUARTZ_COMMON_API ArrayModel : public AbstractTreeModel
{
    Q_OBJECT

public:
    ArrayModel(int numFields,
                bool selectable,
                bool isFlat,
                const QVector<QString> &headers,
                QObject *parent = nullptr);

    ~ArrayModel();

    TreeNode * rootAt(int rowIndex) const override;

    int rootCount() const override;

    void addRoot(TreeNode *node);

    void removeRoot(TreeNode *node);

    bool contains(TreeNode *node);

public Q_SLOTS:
    void clear();

private:
    struct Data;
    std::unique_ptr<Data> m_data;


};

}
