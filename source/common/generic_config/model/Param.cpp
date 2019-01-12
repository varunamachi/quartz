#include <QString>
#include <QVector>
#include <QVariant>

#include "Param.h"

namespace Quartz {

struct Param::Data
{
    Data(const QString &id,
          const QString &name,
          const QString &description)
        : m_id(id)
        , m_name(name)
        , m_description(description)
    {
    }

    QString m_id;

    QString m_name;

    QString m_description;

};

Param::Param(const QString &id,
              const QString &name,
              const QString &description,
              TreeNode *parent)
    : TreeNode(2, parent)
    , m_data(std::make_unique<Data>(id, name, description))
{

}

Param::~Param()
{

}

const QString & Param::id() const
{
    return m_data->m_id;
}

const QString & Param::name() const
{
    return m_data->m_name;
}

const QString & Param::description() const
{
    return m_data->m_description;
}

QVariant Param::fieldValue(int field) const
{
    switch(field) {
    case 0: return m_data->m_name;
    case 1: return this->value();
    }
    return QVariant{};
}

bool Param::setData(int field, const QVariant &value)
{
    if (field < 2) {
        switch(field) {
        case 0: m_data->m_name = value.toString(); break;
        case 1: this->setValue(value); break;
        }
        return true;
    }
    return false;
}

bool Param::isEditable(int field) const
{
    return field == 1;
}

}
