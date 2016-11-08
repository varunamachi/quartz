#pragma once

#include <QAbstractItemModel>

#include <core/extension_system/IPluginAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class Node;
using NodePtr = std::shared_ptr< Node >;

class QUARTZ_BASE_API SelectionTree : public QAbstractItemModel
                                    , public IPluginAdapter

{
    Q_OBJECT

public:
    SelectionTree( QObject *parent = 0 );

    ~SelectionTree();

    bool addNode( const QStringList &parentPath, const NodePtr node );

    bool removeNode( const QStringList &path );

    bool selectNode( const QStringList &path ) const;

    const Node * node( const QStringList &path ) const;


    static const QString ADAPTER_NAME;

public:
    const QString &pluginType() const override;

    const QString &pluginAdapterName() const override;

    bool handlePlugin( IPlugin *plugin ) override;

    bool finalizePlugins() override;

public:
    QModelIndex index( int row,
                       int column,
                       const QModelIndex &parent ) const override;

    QModelIndex parent( const QModelIndex &child ) const override;

    int rowCount( const QModelIndex &parent ) const override;

    int columnCount( const QModelIndex &parent ) const override;

    QVariant data( const QModelIndex &index, int role ) const override;

    bool hasChildren( const QModelIndex &parent ) const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

    Node * traverse( Node *node,
                     const QStringList &path,
                     bool tillParent,
                     int depth ) const;

    Node * createPath( Node *node,
                       const QStringList &path,
                       int depth );
};

}
