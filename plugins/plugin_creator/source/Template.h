#pragma once

#include <memory>

#include <QString>

#include <common/model_view/ITreeNode.h>

namespace Quartz { namespace Plugin { namespace Creator {

class Variable;

class Template : public ITreeNode
{
public:
    explicit Template( const QString &name,
                       const QString &content );

    ~Template();

    QString name() const;

    void addVariable( const QString &key,
                      const QString &value,
                      const QString &description );

    const Variable & variable( const QString &key ) const;

    const Variable & variableAt( int index ) const;

    const QString & content() const;

    int numChildren() const override;

    int numFields() const override;

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

    static const Variable EMPTY_VARIABLE;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
