#pragma once

#include <QAbstractItemModel>

#include <core/extension_system/IPluginAdapter.h>

namespace Quartz {

class Node;
using NodePtr = std::shared_ptr< Node >;

class SelectionTree : public IPluginAdapter
                      , public QAbstractItemModel
{
    Q_OBJECT
public:

    bool addNode( const QStringList &parentPath, const NodePtr node );

    bool removeNode( const QStringList &path );

    bool selectNode( const QStringList &path ) const;

    const Node * node( const QStringList &path ) const;


    static const QString ADAPTER_NAME;

public:
    const QString &pluginType() const;

    const QString &pluginAdapterName() const;

    bool handlePlugin( IPlugin *plugin );

    bool finalizePlugins();

public:
    QModelIndex index( int row, int column, const QModelIndex &parent ) const;

    QModelIndex parent( const QModelIndex &child ) const;

    int rowCount( const QModelIndex &parent ) const;

    int columnCount( const QModelIndex &parent ) const;

    QVariant data( const QModelIndex &index, int role ) const;

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
