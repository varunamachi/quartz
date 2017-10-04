#pragma once

#include <memory>

#include "../model_view/ITreeNode.h"

class QString;

namespace Quartz {

class Template;

class TemplateInstance : public ITreeNode
{

public:
    TemplateInstance( const QString &name,
                      Template *parent );

    ~TemplateInstance();

    const QString & name() const;

    Template * instanceOf() const;

    void setParamValue( const QString &paramName,
                           const QString &paramValue );

    QString paramValue( const QString &paramName ) const;

    int numChildren() const override;

    int numFields() const override;

    ITreeNode * child(int row) const override;

    QVariant data(int column) const override;

    void setSelected( bool value ) override;

    bool isSelected() const override;

    ITreeNode * parent() const override;

    int indexOfChild( const ITreeNode *child ) const override;

    bool isEditable( int column ) const override;

    void setData( int column, const QVariant &data ) override;

    void addChild( std::shared_ptr< ITreeNode > child ) override;

    void removeChild( const ITreeNode *child ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}