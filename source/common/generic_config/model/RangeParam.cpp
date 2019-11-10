#include <QVariant>
#include <QString>

#include "RangeParam.h"

namespace Quartz {

struct RangeParam::Data {
    Data()
        : m_min(0x0)
        , m_max(0x7FFFFFFF)
        , m_defaultValue(m_min)
        , m_inc(1)
        , m_value(m_defaultValue) {
    }

    int m_min;

    int m_max;

    int m_defaultValue;

    int m_inc;

    int m_value;
};

RangeParam::RangeParam(const QString& id,
                       const QString& name,
                       const QString& description,
                       TreeNode* parent)
    : Param(id, name, description, parent)
    , m_data(std::make_unique<Data>()) {
}

RangeParam::~RangeParam() {
}

int RangeParam::maxVal() const {
    return m_data->m_max;
}

void RangeParam::setMax(int max) {
    m_data->m_max = max;
}

int RangeParam::minVal() const {
    return m_data->m_min;
}

void RangeParam::setMin(int min) {
    m_data->m_min = min;
}

int RangeParam::inc() const {
    return m_data->m_inc;
}

void RangeParam::setIncrement(int inc) {
    m_data->m_inc = inc;
}

int RangeParam::defaultValue() const {
    return m_data->m_defaultValue;
}

void RangeParam::setDefaultValue(int defaultValue) {
    m_data->m_defaultValue = defaultValue;
}

ParamType RangeParam::type() const {
    return ParamType::Range;
}

QVariant RangeParam::value() const {
    return QVariant{m_data->m_value};
}

void RangeParam::setValue(const QVariant& value) {
    bool ok = false;
    int val = value.toInt(&ok);
    if (ok && val >= m_data->m_min && val <= m_data->m_max) {
        m_data->m_value = val;
    }
}

std::unique_ptr<Param> RangeParam::clone() const {
    auto param = std::make_unique<RangeParam>(
        id(), name(), description(), parent());
    param->setMax(this->maxVal());
    param->setMin(this->minVal());
    param->setIncrement(this->inc());
    param->setDefaultValue(this->defaultValue());
    return std::move(param);
}

} // namespace Quartz
