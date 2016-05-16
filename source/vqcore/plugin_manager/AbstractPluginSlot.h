
#pragma once

#include <memory>

#include "../VQCommon.h"
#include "../common/Result.h"


class std::string;

namespace Vam {

class AbstractPlugin;

class AbstractPluginSlot
{
public:
    AbstractPluginSlot( const std::string &slotId,
                        const std::string &slotName,
                        const std::string &slotDescription );

    const std::string & slotId() const;

    const std::string & slotName() const;

    const std::string & slotDescription() const;

    virtual ~AbstractPluginSlot();

    virtual Result< bool > handlePlugin( AbstractPlugin *plugin ) = 0;

    virtual Result< bool > finalizePlugin( AbstractPlugin *plugin ) = 0;

private:
    class Data;
    std::unique_ptr< Data > m_data;
};

}
