
#include <QVariant>
#include <QString>

#include "TextParam.h"

namespace Quartz {


struct TextParam::Data
{
    Data( TextType type, const QString &defValue )
        : m_textType{ type }
        , m_defaultValue{ defValue }
        , m_value{ defValue }
    {

    }

    TextType m_textType;

    QString m_defaultValue;

    QString m_value;
};

TextParam::TextParam( const QString &id,
                    const QString &name,
                    const QString &description,
                    TreeNode *parent )
    : Param{ id, name, description, parent }
    , m_data{ new Data{ TextType::Any, "" }}
{

}

TextParam::~TextParam()
{

}

ParamType TextParam::type() const
{
    return ParamType::Text;
}

QVariant TextParam::value() const
{
    return QVariant{ m_data->m_value };
}

void TextParam::setValue( const QVariant &value )
{
    m_data->m_value = value.toString();
}

TextType TextParam::textType() const
{
    return m_data->m_textType;
}

void TextParam::setTextType( TextType textType )
{
    m_data->m_textType = textType;
}

const QString & TextParam::defaultValue() const
{
    return m_data->m_defaultValue;
}

void TextParam::setDefaultValue( const QString &defaultValue )
{
    m_data->m_defaultValue = defaultValue;
}


}
