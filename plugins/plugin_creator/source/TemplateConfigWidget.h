#pragma once

#include <memory>

#include <QWidget>

#include <common/model_view/AbstractTreeModel.h>

class QModelIndex;

namespace Quartz {

class Template;
class TemplateInstance;
class Config;
class TreeNode;

namespace Ext { namespace Creator {

class TemplateManager;

class ConfigModel : public AbstractTreeModel
{
    Q_OBJECT
public:
    explicit ConfigModel(QObject *parent);

    ~ConfigModel() override;

    void setConfig(Config *config);

protected:
    TreeNode *rootAt(int index) const override;

    int rootCount() const override;

    int indexOfRoot(TreeNode *node) const override;

private:
    Config *m_config;
};

/**
 * @brief The TemplateConfigWidget class allows configuring selected templates
 */
class TemplateConfigWidget : public QWidget
{
    Q_OBJECT
public:
    TemplateConfigWidget(
            TemplateManager *tman,
            QWidget *parent = nullptr);

    ~TemplateConfigWidget();

    TemplateInstance * createInstanceOf(Template *tmpl);

    int numInstances() const;

    TemplateInstance * instanceAt(int index);

    void clear();

public Q_SLOTS:
    void onSelection(const QModelIndex &cur, const QModelIndex &prev);

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

} } }
