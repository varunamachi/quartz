#pragma once

#include <memory>

#include <QVector>

#include "../QuartzCore.h"
#include "../utils/Macros.h"

class QString;
class QStringList;

namespace Quartz {

class QUARTZ_CORE_API AbstractPlugin
{

public:
    AbstractPlugin( const QString &pluginId,
                    const QString &pluginName,
                    const QString &pluginType );

    virtual ~AbstractPlugin();

    const QString & pluginId() const;

    const QString & pluginName() const;

    const QString & pluginType() const;

    virtual bool init() = 0;

    virtual bool destroy() = 0;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}

