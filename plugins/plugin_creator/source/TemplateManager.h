#pragma once

#include <memory>

#include <QList>
#include <QAbstractItemModel>

#include <core/ext/IExtensionAdapter.h>

#include <common/model_view/AbstractTreeModel.h>


namespace Quartz {

class Template;

namespace Ext { namespace Creator {

class TemplateManager : public AbstractTreeModel
                      , public IExtensionAdapter
{
    Q_OBJECT
public:
    explicit TemplateManager();

    ~TemplateManager();

    void addTemplate(std::shared_ptr<Template> tmplt);

    QList< Template *> templates() const;

    const QString &extensionType() const override;

    const QString &extensionAdapterName() const override;

    bool handleExtension(Extension *plugin) override;

    bool finalizeExtension() override;

    void addVariable(const QString &key, const QString &value);

    QString variable(const QString &key);

    Template * templateAt(int index) const;

    int numTemplates() const;

    bool loadCoreTemplates();

    void selectAll();

    void deselectAll();

    static const QString ADAPTER_NAME;

protected:
    TreeNode *rootAt(int rowIndex) const override;

    int rootCount() const override;

    int indexOfRoot(TreeNode *node) const override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;


};


} } }
