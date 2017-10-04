#pragma once

#include <memory>
#include <cstdint>


class QString;
class QVariant;

namespace Quartz {

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
    Param( const QString &id,
           const QString &name,
           const QString &description );

    virtual ~Param();

    const QString &id() const;

    const QString & name() const;

    const QString & description() const;

    virtual QVariant value() const = 0;

    virtual void setValue( const QVariant &value ) = 0;

    virtual ParamType type() const = 0;



private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}