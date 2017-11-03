#pragma once

#include <memory>

#include "AbstractTreeModel.h"

namespace Quartz {

class ArrayModel : public AbstractTreeModel
{
    Q_OBJECT

public:
    ArrayModel( QObject *parent = nullptr );

    ~ArrayModel();

    void setRoots( QVector< ITreeNode *> roots );

    ITreeNode * rootAt( int rowIndex ) const override;

    int rootCount() const override;

    void addRoot( ITreeNode *node );

    void removeRoot( ITreeNode *node );

    bool contains( ITreeNode *node );

private:
    struct Data;
    std::unique_ptr< Data > m_data;


};

}
