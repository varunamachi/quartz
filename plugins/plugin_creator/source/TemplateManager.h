#pragma once

#include <memory>

#include <QList>
#include <QAbstractItemModel>

#include <core/extension_system/IPluginAdapter.h>

#include <common/model_view/AbstractTreeModel.h>


namespace Quartz {

class Template;

namespace Plugin { namespace Creator {

class TemplateManager : public AbstractTreeModel
                      , public IPluginAdapter
{
    Q_OBJECT
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

    Template * templateAt( int index ) const;

    int numTemplates() const;

    bool loadCoreTemplates();

    static const QString ADAPTER_NAME;

protected:

    TreeNode *rootAt(int rowIndex) const override;

    int rootCount() const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;


};


} } }
