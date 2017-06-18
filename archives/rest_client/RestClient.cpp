
#include "RestClient.h"

namespace Quartz {

class RestClient::Data
{

};

RestClient::RestClient( QObject *parent )
    : QObject{ parent }
    , m_data( new Data{} )
{

}

RestClient::~RestClient()
{

}



}
