
#include "GenInfo.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct GenInfo::Data
{

};

GenInfo::GenInfo()
    : m_data{ new Data{} }
{

}

GenInfo::~GenInfo()
{

}

} } }
