#pragma once

#include <memory>

#include <QHash>

#include "../QuartzCommon.h"
#include "../model_view/TreeNode.h"

namespace Quartz {

class Template;
class Config;
class Param;

using GlobalConfig = QHash< QString, QVariant >;

class QUARTZ_COMMON_API TemplateInstance : public TreeNode
{

public:
    TemplateInstance( const QString &name,
                      std::unique_ptr< Config > config,
                      Template *parent );

    ~TemplateInstance();

    const QString & name() const;

    Template * instanceOf() const;

    void setGlobalConfig( std::shared_ptr< GlobalConfig > gconf );

    QVariant globalConfig( const QString &key ) const;

    const Param * param( const QString &paramName ) const;

    Param * param( const QString &paramName );

    QVariant paramValue( const QString &paramName,
                         const QString defValue = "" ) const;

    QVariant fieldValue( int field ) const override;

    bool isEditable( int column ) const override;

    bool setData( int column, const QVariant &data ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
