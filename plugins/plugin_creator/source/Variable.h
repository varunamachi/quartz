#pragma once

#include <memory>

#include <common/model_view/ITreeNode.h>

class QString;

namespace Quartz { namespace Plugin { namespace Creator {

class Variable
{
public:
    Variable( const QString &name,
              const QString &description,
              const QString &defaultValue );

    ~Variable();

    const QString & name() const;

    const QString & defaultValue() const;

    const QString & description() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
