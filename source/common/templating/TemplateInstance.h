#pragma once

#include <memory>

#include <QHash>

#include "../QuartzCommon.h"
#include "../model_view/TreeNode.h"

namespace Quartz {

class Template;

using GlobalConfig = QHash< QString, QVariant >;

class QUARTZ_COMMON_API TemplateInstance : public TreeNode
{

public:
    TemplateInstance( const QString &name,
                      Template *parent );

    ~TemplateInstance();

    const QString & name() const;

    Template * instanceOf() const;

    void setParamValue( const QString &paramName,
                        const QVariant &paramValue );

    void setGlobalConfig( std::shared_ptr< GlobalConfig > gconf );

    QVariant globalConfig( const QString &key ) const;

    QVariant paramValue( const QString &paramName ) const;

    QVariant  paramValue( const QString &paramName,
                          const QString &defValue ) const;

    int numChildren() const override;

    int numFields() const override;

    bool isSelectable() const override;

    TreeNode * child(int row ) const override;

    QVariant data( int column ) const override;

    void setSelected( bool value ) override;

    bool isSelected() const override;

    TreeNode * parent() const override;

    int indexOfChild( const TreeNode *child ) const override;

    bool isEditable( int column ) const override;

    void setData( int column, const QVariant &data ) override;

    void addChild( std::shared_ptr< TreeNode > child ) override;

    void removeChild( const TreeNode *child ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
