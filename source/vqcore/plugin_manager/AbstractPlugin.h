#pragma once

#include <memory>

#include "../VQCommon.h"
#include "../common/Result.h"

class QString;

namespace Vam {

class AbstractPlugin
{
public:
    AbstractPlugin( const QString &pluginId,
                    const QString &pluginType,
                    const QString &pluginName,
                    const QString &pluginDesc );

    virtual ~AbstractPlugin();

    const QString & pluginId() const;

    const QString & pluginType() const;

    const QString & pluginName() const;

    const QString & pluginDescription() const;

    virtual Result< bool > init() = 0;

    virtual Result< bool > uninit() = 0;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;


};

}
