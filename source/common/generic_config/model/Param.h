#pragma once

#include <memory>
#include <cstdint>

#include "../../QuartzCommon.h"
#include "../../model_view/TreeNode.h"

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


class QUARTZ_COMMON_API Param : public TreeNode
{
public:
    Param( const QString &id,
           const QString &name,
           const QString &description,
           TreeNode *parent );

    virtual ~Param();

    const QString &id() const;

    const QString & name() const;

    const QString & description() const;

    QVariant fieldValue( int field ) const override;

    bool setData( int field, const QVariant &value ) override;

    virtual QVariant value() const = 0;

    virtual void setValue( const QVariant &value ) = 0;

    virtual ParamType type() const = 0;

    bool isEditable( int field ) const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
