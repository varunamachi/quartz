#pragma once

#include <memory>
#include <cstdint>

#include <QString>
#include <QList>
#include <QHash>

namespace Vam { namespace Quartz {

enum class ParamType
{
    Boolean,
    Choice,
    Range,
    Text
};


class Param
{
public:
    typedef std::shared_ptr< Param > Ptr;

    Param( const QString &id,
           const QString &name,
           const QString &category )
        : m_id( id )
        , m_name( name )
        , m_category( category )
    {

    }

    virtual ~Param()
    {

    }

    const QString &id() const
    {
        return m_id;
    }

    const QString & name() const
    {
        return m_name;
    }

    const QString & category() const
    {
        return m_category;
    }

    void addSubParam( Param::Ptr param )
    {
        m_subParams.append( param );
    }

    const QList< Param::Ptr > & subParams()
    {
        return m_subParams;
    }

    Param::Ptr subParam( std::size_t index )
    {
        Param::Ptr subParam = nullptr;
        if( index < m_subParams.size() ) {
            subParam = m_subParams.at( index );
        }
        return subParam;
    }

    virtual ParamType type() const = 0;

private:
    QString m_id;

    QString m_name;

    QString m_category;

    QList< Param::Ptr > m_subParams;

};


class BooleanParam : public Param
{
public:
    BooleanParam( const QString &id,
                  const QString &name,
                  const QString &category )
        : Param( id, name, category )
        , m_default( false )
    {

    }

    void setDefaultValue( bool value )
    {
        m_default = value;
    }

    bool defaultValue() const
    {
        return m_default;
    }

    ParamType type() const
    {
        return ParamType::Boolean;
    }

private:
    bool m_default;

};


class ChoiceParam : public Param
{
public:
    explicit ChoiceParam( const QString &id,
                          const QString &name,
                          const QString &category )
        : Param( id, name, category )
        , m_defaultIndex( -1 )
    {
    }

    void addChoice( const QString &name, const QString &value )
    {

        if( ! m_choices.contains( name )) {
            m_names.append( name );
            m_choices.insert( name, value );
        }
        if( m_defaultIndex == -1 ) {
            m_defaultIndex = 0;
        }
    }

    QString value( const QString &name ) const
    {
        QString value = m_choices.value( name, "" );
        return value;
    }

    QString value( std::size_t index ) const
    {
        QString result = "";
        if( m_names.size() > index ) {
            result = m_names.at( index );
        }
        return result;
    }

    ParamType type() const
    {
        return ParamType::Choice;
    }

    int defaultIndex() const
    {
        return m_defaultIndex;
    }

    void setDefaultIndex( int defaultIndex )
    {
        m_defaultIndex = defaultIndex;
    }

    std::size_t count() const
    {
        return m_choices.size();
    }

private:
    QList< QString > m_names;

    QHash< QString, QString > m_choices;

    int m_defaultIndex;
};


class RangeParam : public Param
{
public:
    RangeParam( const QString &id,
                const QString &name,
                const QString &category )
        : Param( id, name, category )
        , m_min( 0x0 )
        , m_max( 0xFFFFFFFF )
        , m_inc( 1 )
        , m_defaultValue( m_min )
    {

    }

    std::size_t maxVal() const
    {
        return m_max;
    }

    void setMax( std::size_t max )
    {
        m_max = max;
    }

    std::size_t minVal() const
    {
        return m_min;
    }

    void setMin( std::size_t min )
    {
        m_min = min;
    }

    std::uint8_t inc() const
    {
        return m_inc;
    }

    void setIncrement( std::uint8_t inc )
    {
        m_inc = inc;
    }

    std::size_t defaultValue() const
    {
        return m_defaultValue;
    }

    void setDefaultValue( std::size_t defaultValue )
    {
        m_defaultValue = defaultValue;
    }

    ParamType type() const
    {
        return ParamType::Range;
    }

private:
    std::size_t m_max;

    std::size_t m_min;

    std::uint8_t m_inc;

    std::size_t m_defaultValue;
};


class TextParam : public Param
{
public:
    enum class TextType
    {
        Any,
        Identifier,
        Alphanumeric,
        Hexadecimal,
        Decimal,
        Binary
    };

    explicit TextParam( const QString &id,
                        const QString &name,
                        const QString &category )
        : Param( id, name, category )
        , m_textType( TextType::Any )
        , m_defaultValue( "" )
    {

    }

    ParamType type() const
    {
        return ParamType::Text;
    }

    TextType textType() const
    {
        return m_textType;
    }

    void setTextType( TextType textType )
    {
        m_textType = textType;
    }

    const QString & defaultValue() const
    {
        return m_defaultValue;
    }

    void setDefaultValue( const QString &defaultValue )
    {
        m_defaultValue = defaultValue;
    }

private:
    TextType m_textType;

    QString m_defaultValue;
};

} }
