#pragma once

#include <memory>

#include <QString>

#include "../QuartzCommon.h"
#include "../model_view/TreeNode.h"

namespace Quartz {

class Config;

class QUARTZ_COMMON_API Template : public TreeNode
{
public:
    explicit Template( const QString &name,
                       const QString &content );

    ~Template() override;

    QString name() const;

    void setConfig( std::unique_ptr< Config > config );

    Config * config() const;

    const QString & content() const;

    QVariant fieldValue( int field ) const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
