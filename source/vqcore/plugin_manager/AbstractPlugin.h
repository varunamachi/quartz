#pragma once

#include <memory>
#include <string>

#include "../common/Result.h"
#include "../VQ.h"

namespace Vq {

class VQ_API AbstractPlugin
{
public:
    AbstractPlugin( const std::string &pluginId,
                    const std::string &pluginType,
                    const std::string &pluginName,
                    const std::string &pluginDesc );

    virtual ~AbstractPlugin();

    const std::string & pluginId() const;

    const std::string & pluginType() const;

    const std::string & pluginName() const;

    const std::string & pluginDescription() const;

    virtual Result< bool > init() = 0;

    virtual Result< bool > uninit() = 0;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;


};

using AbstractPluginUPtr = std::unique_ptr< AbstractPlugin >;

}
