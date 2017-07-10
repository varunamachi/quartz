#pragma once

#include <memory>

#include "ITreeNode.h"

class QString;

namespace Quartz { namespace Plugin { namespace Creator {

class Variable : public ITreeNode
{
public:
    Variable( const QString &name,
              const QString &description,
              const QString &value );

    ~Variable();

    const QString & name() const;

    const QString & value() const;

    const QString & description() const;

    int numChildren() const override;

    int numFields() const override;

    ITreeNode*child(int row) const override;

    QVariant data(int column) const override;

    void setSelected( bool value ) override;

    bool isSelected() override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
