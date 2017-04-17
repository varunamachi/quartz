
#include "SerialDeviceManager.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

std::unique_ptr< SerialDeviceManager > SerialDeviceManager::s_instance{
    nullptr };

struct SerialDeviceManager::Data
{

};

SerialDeviceManager *SerialDeviceManager::instance()
{
    if( ! s_instance ) {
        s_instance = std::unique_ptr< SerialDeviceManager >{
                new SerialDeviceManager{ }};

    }
    return s_instance.get();
}

void SerialDeviceManager::destroy()
{
    s_instance.reset();
}

SerialDeviceManager::SerialDeviceManager()
    : m_data{ new Data{ }}
{

}

SerialDeviceManager::~SerialDeviceManager()
{
    //close all the connections
}


} } }
