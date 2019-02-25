#pragma once

#include <memory>

#include "../../QuartzCommon.h"
#include "../../model_view/AbstractTreeModel.h"

namespace Quartz {

class Config;

class QUARTZ_COMMON_API  GenConfigTreeModel : public AbstractTreeModel
{
    Q_OBJECT
public:
    explicit GenConfigTreeModel(QObject *parent);

    ~GenConfigTreeModel() override;

    void setConfig(Config *config);

    void setValues(const QVariantHash &values);

protected:
    TreeNode *rootAt(int rowIndex) const override;

    int rootCount() const override;

    int indexOfRoot(TreeNode *node) const override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

}
