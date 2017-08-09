
#include <QString>

#include "RangeParam.h"

namespace Quartz {

struct RangeParam::Data
{
    Data()
        : m_min( 0x0 )
        , m_max( 0xFFFFFFFF )
        , m_defaultValue( m_min )
        , m_inc( 1 )
    {

    }

    std::size_t m_min;

    std::size_t m_max;

    std::size_t m_defaultValue;

    std::uint8_t m_inc;

};


RangeParam::RangeParam( const QString &id,
                        const QString &name,
                        const QString &category )
    : Param{ id, name, category }
    , m_data{ new Data{ }}
{

}

std::size_t RangeParam::maxVal() const
{
    return m_data->m_max;
}

void RangeParam::setMax( std::size_t max )
{
    m_data->m_max = max;
}

std::size_t RangeParam::minVal() const
{
    return m_data->m_min;
}

void RangeParam::setMin( std::size_t min )
{
    m_data->m_min = min;
}

std::uint8_t RangeParam::inc() const
{
    return m_data->m_inc;
}

void RangeParam::setIncrement( std::uint8_t inc )
{
    m_data->m_inc = inc;
}

std::size_t RangeParam::defaultValue() const
{
    return m_data->m_defaultValue;
}

void RangeParam::setDefaultValue( std::size_t defaultValue )
{
    m_data->m_defaultValue = defaultValue;
}

ParamType RangeParam::type() const
{
    return ParamType::Range;
}

}
