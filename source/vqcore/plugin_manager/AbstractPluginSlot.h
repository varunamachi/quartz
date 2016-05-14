
#pragma once

#include <memory>

#include "../VQCommon.h"
#include "../common/Result.h"


class QString;

namespace Vam {

class AbstractPlugin;

class AbstractPluginSlot
{
public:
    AbstractPluginSlot( const QString &slotId,
                        const QString &slotName,
                        const QString &slotDescription );

    const QString & slotId() const;

    const QString & slotName() const;

    const QString & slotDescription() const;

    virtual Result< bool > handlePlugin( AbstractPlugin *plugin ) = 0;

    virtual Result< bool > finalizePlugin( AbstractPlugin *plugin ) = 0;

private:
    class Data;
    std::unique_ptr< Data > m_data;
};

}
