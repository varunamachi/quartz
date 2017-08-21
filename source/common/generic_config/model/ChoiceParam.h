#pragma once

#include <QPair>

#include "Param.h"

namespace Quartz {

class ChoiceParam : public Param
{
public:
    explicit ChoiceParam( const QString &id,
                          const QString &name,
                          const QString &description );

    ~ChoiceParam();

    void addOption( const QString &name, const QString &value );

    QString optionValue( const QString &name ) const;

    QPair< QString, QString > option( int index ) const;

    int defaultIndex() const;

    void setDefaultIndex( int defaultIndex );

    int numOption() const;

    ParamType type() const override;

    QVariant value() const override;

    void setValue( const QVariant &value ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
