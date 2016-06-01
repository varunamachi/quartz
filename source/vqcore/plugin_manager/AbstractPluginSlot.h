
#pragma once

#include <memory>
#include <string>

#include "../Vq.h"
#include "../common/Result.h"

namespace Vq {

class AbstractPlugin;

class VQ_API AbstractPluginSlot
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
