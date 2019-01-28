#pragma once

#include <memory>

#include <QVector>

#include "../QuartzCore.h"
#include "../utils/Macros.h"

class QString;
class QStringList;

namespace Quartz { namespace Ext {

class QUARTZ_CORE_API Extension
{

public:
    Extension(const QString &extensionId,
               const QString &extensionName,
               const QString &extensionType);

    virtual ~Extension();

    const QString & extensionId() const;

    const QString & extensionName() const;

    const QString & extensionType() const;

    virtual bool init();

    virtual bool destroy();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} }

