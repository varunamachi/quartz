#pragma once

#include <memory>

#include "../../model_view/AbstractTreeModel.h"

namespace Quartz {

class Config;

class GenConfigTreeModel : public AbstractTreeModel
{
    Q_OBJECT
public:
    explicit GenConfigTreeModel( Config *config, QObject *parent );

    ~GenConfigTreeModel();

protected:
    ITreeNode *rootAt(int rowIndex) const;

    int rootCount() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
