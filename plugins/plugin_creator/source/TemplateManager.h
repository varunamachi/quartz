#pragma once

#include <memory>

#include <QList>
#include <QAbstractItemModel>

#include <core/extension_system/IPluginAdapter.h>


namespace Quartz { namespace Plugin { namespace Creator {

class Template;

class TemplateManager : public IPluginAdapter
                      , public QAbstractItemModel
{
public:
    explicit TemplateManager();

    ~TemplateManager();

    void addTemplate( std::shared_ptr< Template> tmplt );

    QList< Template *> templates() const;

    const QString &pluginType() const override;

    const QString &pluginAdapterName() const override;

    bool handlePlugin(AbstractPlugin *plugin) override;

    bool finalizePlugins() override;

    void addVariable( const QString &key, const QString &value );

    QString variable( const QString &key );

//    bool generate( const QString &templateName )

    static const QString ADAPTER_NAME;

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

};


} } }
