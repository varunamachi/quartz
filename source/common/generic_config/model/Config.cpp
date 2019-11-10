#include <QVector>
#include <QHash>
#include <QString>
#include <QVariant>

#include "Config.h"
#include "Param.h"
#include "Group.h"

namespace Quartz {

struct Config::Data {
    Data(const QString& id, const QString& name)
        : m_id(id)
        , m_name(name) {
    }

    QString m_id;

    QString m_name;

    QVector<std::shared_ptr<Param>> m_params;

    QVector<std::shared_ptr<Group>> m_groups;

    QHash<QString, Param*> m_allParams;

    QVariantHash m_constants;
};

Config::Config(const QString& id, const QString& name)
    : TreeNode(1, nullptr)
    , m_data(std::make_unique<Data>(id, name)) {
}

Config::~Config() {
}

const QString& Config::id() const {
    return m_data->m_id;
}

const QString& Config::name() const {
    return m_data->m_name;
}

int Config::numChildParams() const {
    return m_data->m_params.size();
}

Param* Config::childParamAt(int index) const {
    if (index < m_data->m_params.size()) {
        return m_data->m_params.at(index).get();
    }
    return nullptr;
}

void Config::addChildParameter(std::shared_ptr<Param> param) {
    if (param) {
        m_data->m_params.push_back(param);
        registerParam(param.get());
        addChild(param.get());
    }
}

int Config::numGroups() const {
    return m_data->m_groups.size();
}

Group* Config::groupAt(int index) const {
    Group* group = nullptr;
    if (index < m_data->m_groups.size()) {
        group = m_data->m_groups.at(index).get();
    }
    return group;
}

void Config::addGroup(std::shared_ptr<Group> group) {
    if (group != nullptr) {
        m_data->m_groups.append(group);
        addChild(group.get());
    }
}

const Param* Config::param(const QString& id) const {
    Param* param = m_data->m_allParams.value(id, nullptr);
    return param;
}

Param* Config::param(const QString& id) {
    Param* param = m_data->m_allParams.value(id, nullptr);
    return param;
}

bool Config::registerParam(Param* param) {
    bool result = false;
    if (!m_data->m_allParams.contains(param->id())) {
        m_data->m_allParams.insert(param->id(), param);
        result = true;
    }
    return result;
}

QVariant Config::fieldValue(int field) const {
    switch (field) {
    case 0: return m_data->m_name;
    }
    return QVariant{};
}

static void copy(const Config* source, Config* dest) {
    for (auto i = 0; i < source->numGroups(); ++i) {
        dest->addGroup(source->groupAt(i)->clone());
    }
    for (auto i = 0; i < source->numChildParams(); ++i) {
        dest->addChildParameter(source->childParamAt(i)->clone());
    }
}

std::unique_ptr<Config> Config::clone() const {
    auto config = std::unique_ptr<Config>{
        new Config{m_data->m_name, m_data->m_id}};
    copy(this, config.get());
    return config;
}

void Config::setConstant(const QString& key, const QVariant& value) {
    if (m_data->m_constants.contains(key)) {
        m_data->m_constants[key] = value;
    } else {
        m_data->m_constants.insert(key, value);
    }
}

const QVariantHash& Config::constants() const {
    return m_data->m_constants;
}

const QHash<QString, Param*>& Config::allParams() const {
    return m_data->m_allParams;
}

} // namespace Quartz
