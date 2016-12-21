
#include "BundleContext.h"

#include <base/QzAppContext.h>

namespace Quartz { namespace Plugin {

struct BundleContext::Data {
    Data()
        : m_context{ nullptr }
    {

    }

    QzAppContext *m_context;
};

BundleContext::~BundleContext()
{
    m_data->m_context = nullptr;
}

void BundleContext::setAppContext( QzAppContext *context )
{
    m_data->m_context = context;
}

QzAppContext *BundleContext::context()
{
    return m_data->m_context;
}

void BundleContext::destroy()
{
    s_instance.release();
}

BundleContext *BundleContext::instance()
{
    return s_instance.get();
}

BundleContext::BundleContext()
    : m_data{ new Data{ }}
{

}


} }
