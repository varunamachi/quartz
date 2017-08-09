#pragma once

#include "Param.h"

namespace Quartz {

class ChoiceParam : public Param
{
public:
    explicit ChoiceParam( const QString &id,
                          const QString &name,
                          const QString &category );

    ~ChoiceParam();

    void addChoice( const QString &name, const QString &value );

    QString value( const QString &name ) const;

    QString value( int index ) const;

    ParamType type() const override;

    int defaultIndex() const;

    void setDefaultIndex( int defaultIndex );

    int numChoices() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
