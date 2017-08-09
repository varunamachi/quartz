#pragma once

#include "Param.h"

class QString;

namespace Quartz {

class RangeParam : public Param
{
public:
    RangeParam( const QString &id,
                const QString &name,
                const QString &category );

    std::size_t maxVal() const;

    void setMax( std::size_t max );

    std::size_t minVal() const;

    void setMin( std::size_t min );

    std::uint8_t inc() const;

    void setIncrement( std::uint8_t inc );

    std::size_t defaultValue() const;

    void setDefaultValue( std::size_t defaultValue );

    ParamType type() const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
