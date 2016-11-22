#pragma once

#include <memory>

#include <QString>
#include <QStringList>
#include <QVector>

#include "../QuartzCore.h"
#include "../utils/Macros.h"

namespace Quartz {



class QUARTZ_CORE_API AbstractPlugin
{

public:
    AbstractPlugin( const QString &pluginId,
                    const QString &pluginName,
                    const QString &pluginType,
                    const QStringList &dependencies );

    virtual ~AbstractPlugin();

    const QString & pluginId() const;

    const QString & pluginName() const;

    const QString & pluginType() const;

    const QStringList & dependencies() const;

    virtual bool init() = 0;

    virtual bool destroy() = 0;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}

extern "C" {

struct PluginListWrapper {
    QVector< std::shared_ptr< Quartz::AbstractPlugin >>  pluginList;
};

}
