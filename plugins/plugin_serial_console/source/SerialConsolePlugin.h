#pragma once

#include <core/ext/Plugin.h>

namespace Quartz {

class QzAppContext;

namespace Ext { namespace SerialConsole {

class SerialConsolePlugin : public Plugin
{

public:
    SerialConsolePlugin();

    ~SerialConsolePlugin();

    const ExtensionList & extensions() const override;

    const DependencyList & dependencies() const override;

    const AdapterList &adapters() const override;

    static const QString PLUGIN_ID;

    static const QString PLUGIN_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
