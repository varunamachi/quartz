
#include <QString>

#include "RangeParam.h"

namespace Quartz {

struct RangeParam::Data
{
    Data()
        : m_min( 0x0 )
        , m_max( 0x7FFFFFFF )
        , m_defaultValue( m_min )
        , m_inc( 1 )
    {

    }

    int m_min;

    int m_max;

    int m_defaultValue;

    int m_inc;

};


RangeParam::RangeParam( const QString &id,
                        const QString &name,
                        const QString &description )
    : Param{ id, name, description }
    , m_data{ new Data{ }}
{

}

RangeParam::~RangeParam()
{

}

int RangeParam::maxVal() const
{
    return m_data->m_max;
}

void RangeParam::setMax( int max )
{
    m_data->m_max = max;
}

int RangeParam::minVal() const
{
    return m_data->m_min;
}

void RangeParam::setMin( int min )
{
    m_data->m_min = min;
}

int RangeParam::inc() const
{
    return m_data->m_inc;
}

void RangeParam::setIncrement( int inc )
{
    m_data->m_inc = inc;
}

int RangeParam::defaultValue() const
{
    return m_data->m_defaultValue;
}

void RangeParam::setDefaultValue( int defaultValue )
{
    m_data->m_defaultValue = defaultValue;
}

ParamType RangeParam::type() const
{
    return ParamType::Range;
}

}
