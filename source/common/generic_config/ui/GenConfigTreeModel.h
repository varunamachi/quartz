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

    ~GenConfigTreeModel();

    void setConfig(Config *config);

protected:
    TreeNode *rootAt(int rowIndex) const;

    int rootCount() const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
