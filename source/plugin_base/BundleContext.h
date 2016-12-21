#pragma once

#include <memory>

namespace Quartz {

class QzAppContext;

namespace Plugin {

class BundleContext
{
public:
    ~BundleContext();

    void setAppContext( QzAppContext *context );

    QzAppContext * context();

    static void destroy();

    static BundleContext * instance();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

    static std::unique_ptr< BundleContext > s_instance;

    BundleContext();
};


}

}
