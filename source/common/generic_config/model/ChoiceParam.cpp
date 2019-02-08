#include <QVariant>
#include <QString>
#include <QHash>
#include <QVector>

#include "ChoiceParam.h"

namespace Quartz {

struct ChoiceParam::Data {

    Data()
        : m_defaultIndex(0)
        , m_index(m_defaultIndex)
    {

    }

    QVector<QString> m_names;

    QVector<QVariant> m_values;

    int m_defaultIndex;

    int m_index;
};

ChoiceParam::ChoiceParam(const QString &id,
                          const QString &name,
                          const QString &description,
                          TreeNode *parent)
    : Param(id, name, description, parent)
    , m_data{ new Data{} }

{
}

ChoiceParam::~ChoiceParam()
{

}

void ChoiceParam::addOption(const QString &name, const QVariant &value)
{

    if (! m_data->m_names.contains(name)) {
        m_data->m_names.append(name);
        m_data->m_values.append(value);
    }
    if (m_data->m_defaultIndex == -1) {
        m_data->m_defaultIndex = 0;
        m_data->m_index = 0;
    }
}

QPair<QString, QVariant> ChoiceParam::option(int index) const
{
    QPair<QString, QVariant> result;
    if (m_data->m_names.size() > index && index >= 0) {
        result = QPair<QString, QVariant>{
            m_data->m_names[index],
            m_data->m_values[index]
        };
    }
    return result;
}

ParamType ChoiceParam::type() const
{
    return ParamType::Choice;
}

QVariant ChoiceParam::value() const
{
    return this->option(m_data->m_index).second;
}

int ChoiceParam::index() const
{
    return m_data->m_index;
}

void ChoiceParam::setValue(const QVariant &value)
{
    m_data->m_index = m_data->m_values.indexOf(value.toString());
}

int ChoiceParam::defaultIndex() const
{
    return m_data->m_defaultIndex;
}

void ChoiceParam::setDefaultIndex(int defaultIndex)
{
    m_data->m_defaultIndex = defaultIndex;
}

void ChoiceParam::setDefaultValue(const QVariant &value)
{
    auto index = m_data->m_values.indexOf(value);
    if (index != -1) {
        m_data->m_defaultIndex = index;
    }
}

int ChoiceParam::numOption() const
{
    return m_data->m_names.size();
}

std::unique_ptr<Param> ChoiceParam::clone() const
{
    auto param = std::make_unique<ChoiceParam>(
        id(), name(), description(), parent());
    param->setDefaultIndex(this->defaultIndex());

    for (auto i = 0; i < m_data->m_names.size(); ++i) {
        param->addOption(m_data->m_names[i], m_data->m_values[i]);
    }
    return std::move(param);
}

QVariant ChoiceParam::fieldValue(int field) const
{
    if (field == 1) {
        auto index = m_data->m_index >= 0 ? m_data->m_index
                                          : 0;
        return m_data->m_names[index];
    }
    return Param::fieldValue(field);
}

}
