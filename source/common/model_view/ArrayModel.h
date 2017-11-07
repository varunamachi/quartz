#pragma once

#include <memory>

#include "../QuartzCommon.h"
#include "AbstractTreeModel.h"

namespace Quartz {

class QUARTZ_COMMON_API ArrayModel : public AbstractTreeModel
{
    Q_OBJECT

public:
    ArrayModel( QObject *parent = nullptr );

    ~ArrayModel();

    ITreeNode * rootAt( int rowIndex ) const override;

    int rootCount() const override;

    void addRoot( ITreeNode *node );

    void removeRoot( ITreeNode *node );

    bool contains( ITreeNode *node );

    int numItems() const;

    ITreeNode * itemAt( int index ) const;

    void clear();

private:
    struct Data;
    std::unique_ptr< Data > m_data;


};

}
