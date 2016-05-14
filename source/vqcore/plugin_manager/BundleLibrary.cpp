
#include <QLibrary>

#include "BundleLibrary.h"
#include "PluginBundle.h"


namespace Vam
{

class BundleLibrary::Impl
{
public:
    inline Impl()
        : m_library( nullptr )
        , m_bundle( nullptr )
        , m_isValid( false )
    {

    }

    inline Impl( QLibrary *library, PluginBundle *bundle )
        : m_library( library )
        , m_bundle( bundle )
        , m_isValid( library != nullptr && bundle != nullptr )
    {

    }

    inline QLibrary * library() const
    {
        return m_library;
    }

    inline PluginBundle * bundle() const
    {
        return m_bundle;
    }

    inline bool isValid() const
    {
        return m_isValid;
    }

private:
    QLibrary *m_library;

    PluginBundle *m_bundle;

    bool m_isValid;
};


BundleLibrary::BundleLibrary()
    : m_impl( std::make_unique< BundleLibrary::Impl >() )
{

}

BundleLibrary::BundleLibrary( std::unique_ptr< QLibrary > library,
                              std::unique_ptr< PluginBundle > bundle )
    : m_impl( std::make_unique< BundleLibrary::Impl >( library, bundle ))
{

}


QLibrary * BundleLibrary::library() const
{
    m_impl->library();
}


PluginBundle * BundleLibrary::bundle() const
{
    m_impl->bundle();
}


bool BundleLibrary::isValid() const
{
    return m_impl->isValid();
}
