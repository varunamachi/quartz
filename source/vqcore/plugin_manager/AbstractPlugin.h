#pragma once

#include <memory>
#include <string>

#include "../VQCommon.h"
#include "../common/Result.h"



namespace Vam {

class AbstractPlugin
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

}
