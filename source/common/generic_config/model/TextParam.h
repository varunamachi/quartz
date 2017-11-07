#pragma once

#include "Param.h"

#include "../../QuartzCommon.h"

class QString;

namespace Quartz {

enum class TextType
{
    Any,
    Identifier,
    Alphanumeric,
    Hexadecimal,
    Decimal,
    Binary
};

class QUARTZ_COMMON_API  TextParam : public Param
{
public:

    explicit TextParam( const QString &id,
                        const QString &name,
                        const QString &description );

    ~TextParam();

    ParamType type() const override;

    TextType textType() const;

    void setTextType( TextType textType );

    const QString & defaultValue() const;

    void setDefaultValue( const QString &defaultValue );

    QVariant value() const override;

    void setValue( const QVariant &value ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};



}
