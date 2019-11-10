

#include "FixedParam.h"

namespace Quartz {

struct FixedParam::Data {
    explicit Data(const QVariant& val)
        : m_value(val) {
    }

    QVariant m_value;
};

FixedParam::FixedParam(const QString& id,
                       const QString& name,
                       const QString& description,
                       TreeNode* parent,
                       const QVariant& value)
    : Param(id, name, description, parent)
    , m_data(std::make_unique<Data>(value)) {
}

FixedParam::~FixedParam() {
}

QVariant FixedParam::value() const {
    return m_data->m_value;
}

void FixedParam::setValue(const QVariant& /*value*/) {
    // no set
}

ParamType FixedParam::type() const {
    return ParamType::Fixed;
}

bool FixedParam::isEditable(int /*field*/) const {
    return false;
}

std::unique_ptr<Param> FixedParam::clone() const {
    auto param = std::make_unique<FixedParam>(
        id(), name(), description(), parent(), m_data->m_value);
    return std::move(param);
}

} // namespace Quartz
