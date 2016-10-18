#pragma once

#include <memory>

#include <QAbstractItemModel>

#include <core/extension_system/IPluginAdapter.h>

#include "AbstractSelector.h"

namespace Quartz {

class NodeSelector : public AbstractSelector
                   , public IPluginAdapter
                   , public QAbstractItemModel
{
public:
    NodeSelector( QWidget *parent = nullptr );

    ~NodeSelector();

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

    static const QString ADAPTER_NAME;

    static const QString PLUGIN_TYPE;

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

    inline Data * d()
    {
        return m_data.get();
    }

    void setupLayout();



    // IPluginAdapter interface

    // QAbstractItemModel interface
};



}
