
#include <QDir>
#include <QHash>

#include <common/templating/Template.h>
#include <common/templating/TemplateUtils.h>

#include "TemplateManager.h"
#include "AbstractTemplateProvider.h"


namespace Quartz { namespace Ext { namespace Creator {

const QVector<QString> HEADERS{
    QObject::tr("Templates")
};

const QString TemplateManager::ADAPTER_NAME("Template Adapter");

struct TemplateManager::Data {

    explicit Data() { }

    QHash< QString, std::shared_ptr<Template>> m_templates;

    QHash< QString, QString > m_variables;

    QList< Template *> m_templateList;
};

TemplateManager::TemplateManager()
    : AbstractTreeModel{
          nullptr,
          AbstractTreeModel::Options(1, true, true, HEADERS)}
    , m_data{ new Data{} }
{

}

TemplateManager::~TemplateManager()
{

}

void TemplateManager::addTemplate(std::shared_ptr<Template> tmplt)
{
    m_data->m_templates.insert(tmplt->name(), tmplt);
    m_data->m_templateList.push_back(tmplt.get());
}

QList< Template *> TemplateManager::templates() const
{
    QList< Template *> templates;
    foreach(auto &ptr, m_data->m_templates.values()) {
        templates.push_back(ptr.get());
    }
    return templates;
}

const QString &TemplateManager::extensionType() const
{
    return AbstractTemplateProvider::EXTENSION_TYPE;
}

const QString &TemplateManager::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool TemplateManager::handleExtension(Extension *extension)
{
    auto tmpProvider = dynamic_cast<AbstractTemplateProvider *>(extension);
    if (tmpProvider != nullptr) {
        auto templates = tmpProvider->templates();
        foreach(auto &tmpl, templates) {
            addTemplate(tmpl);
        }
    }
    return true;
}

bool TemplateManager::finalizeExtension()
{
    m_data->m_templates.clear();
    return true;
}

void TemplateManager::addVariable(const QString& key, const QString& value)
{
    m_data->m_variables.insert(key, value);
}

QString TemplateManager::variable(const QString& key)
{
    return m_data->m_variables.value(key);
}

Template * TemplateManager::templateAt(int index) const
{
    if (index < m_data->m_templateList.size()) {
        return m_data->m_templateList.at(index);
    }
    return nullptr;
}

int TemplateManager::numTemplates() const
{
    return m_data->m_templateList.size();
}


bool TemplateManager::loadCoreTemplates()
{
//    beginResetModel();
//    const QDir resDir{ ":/resources" };
//    auto tmps = TemplateUtils::templatesInDir(resDir);
//    foreach(auto &tmpl, tmps) {
//        addTemplate(tmpl);
//    }
//    endResetModel();
    return true;
}

void TemplateManager::selectAll()
{
    if (! m_data->m_templateList.isEmpty()) {
        beginResetModel();
        for (auto t : m_data->m_templateList) {
            t->setSelected(true);
        }
        endResetModel();
    }
}

void TemplateManager::deselectAll()
{
    if (! m_data->m_templateList.isEmpty()) {
        beginResetModel();
        for (auto t : m_data->m_templateList) {
            t->setSelected(false);
        }
        endResetModel();
    }
}

TreeNode * TemplateManager::rootAt(int rowIndex) const
{
    if (rowIndex < m_data->m_templateList.size()) {
        return m_data->m_templateList.at(rowIndex);
    }
    return nullptr;
}

int TemplateManager::rootCount() const
{
    return m_data->m_templateList.size();
}

int TemplateManager::indexOfRoot(TreeNode *node) const
{
    auto tmpl = dynamic_cast<Template *>(node);
    if (tmpl != nullptr) {
        return m_data->m_templateList.indexOf(tmpl);
    }
    return -1;
}

} } }
