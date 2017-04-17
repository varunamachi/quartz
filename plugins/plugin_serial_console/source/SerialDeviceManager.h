#pragma once

#include <memory>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class SerialDeviceManager
{
public:
    static SerialDeviceManager * instance();

    static void destroy();

    ~SerialDeviceManager();

private:
    struct Data;

    SerialDeviceManager();


    static std::unique_ptr< SerialDeviceManager > s_instance;

    std::unique_ptr< Data > m_data;

};

} } }
