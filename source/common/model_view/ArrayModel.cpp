
#include <QVector>

#include "ITreeNode.h"
#include "ArrayModel.h"

namespace Quartz {

struct ArrayModel::Data
{
    QVector< ITreeNode *> m_roots;
};

ArrayModel::ArrayModel( QObject *parent )
    : AbstractTreeModel{ parent }
    , m_data{ new Data{} }
{

}

ArrayModel::~ArrayModel()
{

}

ITreeNode * ArrayModel::rootAt( int rowIndex ) const
{
    ITreeNode *root = nullptr;
    if( rowIndex < m_data->m_roots.size() ) {
        root = m_data->m_roots[ rowIndex ];
    }
    return root;
}

int ArrayModel::rootCount() const
{
    return m_data->m_roots.size();
}

void ArrayModel::addRoot( ITreeNode *node )
{
    beginResetModel();
    m_data->m_roots.push_back( node );
    endResetModel();
}

void ArrayModel::removeRoot( ITreeNode *node )
{
    beginResetModel();
    m_data->m_roots.removeAll( node );
    endResetModel();
}

bool ArrayModel::contains( ITreeNode *node )
{
    return m_data->m_roots.contains( node );
}

}
