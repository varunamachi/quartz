#pragma once

#include <memory>

#include <QString>

#include "../QuartzCommon.h"
#include "../model_view/ITreeNode.h"

namespace Quartz {

class Config;

class QUARTZ_COMMON_API Template : public ITreeNode
{
public:
    explicit Template( const QString &name,
                       const QString &content );

    ~Template();

    QString name() const;

    void setConfig( std::unique_ptr< Config > config );

    Config * config() const;

    const QString & content() const;

    int numChildren() const override;

    int numFields() const override;

    bool isSelectable() const override;

    ITreeNode * child( int row ) const override;

    QVariant data( int column ) const override;

    void setSelected(bool value) override;

    bool isSelected() const override;

    ITreeNode * parent () const override;

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
