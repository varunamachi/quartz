#include <QString>
#include <QVariant>

#include "../generic_config/model/Config.h"
#include "../generic_config/model/Param.h"

#include "Template.h"
#include "TemplateInstance.h"

namespace Quartz {

struct TemplateInstance::Data
{
    Data(const QString &name,
          std::unique_ptr<Config> config,
          Template *parent)
     : m_name(name)
     , m_config(std::move(config))
     , m_parent(parent)
     , m_selected(false)
    {

    }

    QString m_name;

    std::unique_ptr<Config> m_config;

    Template *m_parent;

    bool m_selected;

    std::shared_ptr<GlobalConfig> m_globalConfig;
};

TemplateInstance::TemplateInstance(const QString &name,
                                    std::unique_ptr<Config> config,
                                    Template *parent)
    : TreeNode(1, parent)
    , m_data(std::make_unique<Data>(name, std::move(config), parent))
{

}

TemplateInstance::~TemplateInstance()
{

}

const QString & TemplateInstance::name() const
{
    return m_data->m_name;
}

Template * TemplateInstance::instanceOf() const
{
    return m_data->m_parent;
}

void TemplateInstance::setGlobalConfig(std::shared_ptr<GlobalConfig> gconf)
{
    m_data->m_globalConfig = gconf;
}

QVariant TemplateInstance::globalConfig(const QString &key) const
{
    return m_data->m_globalConfig->value(key);
}

const Param * TemplateInstance::param(const QString &paramName) const
{
    auto param = m_data->m_config->param(paramName);
    return param;
}

Param *TemplateInstance::param(const QString &paramName)
{
    auto param = m_data->m_config->param(paramName);
    return param;
}

QVariant TemplateInstance::paramValue(const QString &paramName,
                                       const QString defValue) const
{
    auto val = m_data->m_globalConfig->value(paramName);
    auto param = m_data->m_config->param(paramName);
    if (param != nullptr) {
        return param->value();
    }
    return val.isValid() ? val : defValue;
}

QVariant TemplateInstance::fieldValue(int column) const
{
    switch(column) {
    case 0: return m_data->m_name;
    }
    return QVariant{};
}

bool TemplateInstance::isEditable(int column) const
{
    return column == 0;
}

bool TemplateInstance::setData(int column, const QVariant &data)
{
    if (column == 0) {
        m_data->m_name= data.toString();
        return true;
    }
    return false;
}

Config * TemplateInstance::instanceConfig()
{
    return m_data->m_config.get();
}

QVariantHash TemplateInstance::allParams() const
{
    QVariantHash out;
    m_data->m_config->setConstant("NAME", name());
    for (auto it = m_data->m_globalConfig->begin();
        it != m_data->m_globalConfig->end();
        ++ it) {
        out[it.key()] = it.value();
    }
    for (auto it = m_data->m_config->allParams().begin();
        it != m_data->m_config->allParams().end();
        ++ it) {
        out[it.key()] = it.value()->value();
    }
    for (auto it = m_data->m_config->constants().begin();
         it != m_data->m_config->constants().end();
         ++ it) {
        out[it.key()] = it.value();
    }
    return out;
}

const Config * TemplateInstance::instanceConfig() const
{
    return m_data->m_config.get();
}

}
