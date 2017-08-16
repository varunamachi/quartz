#pragma once

#include "../../model_view/ITreeNode.h"

namespace Quartz {

class Config;

class ConfigTreeNode : public ITreeNode
{
public:
    ConfigTreeNode( ITreeNode *parent, Config *config );

    ~ConfigTreeNode();

    int numChildren() const override;

    int numFields() const override;

    ITreeNode * child( int row ) const override;

    QVariant data( int column ) const override;

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
