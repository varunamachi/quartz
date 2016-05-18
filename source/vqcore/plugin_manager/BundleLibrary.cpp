
#include "../platform/shared_library/SharedLibrary.h"

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

    inline Impl( std::unique_ptr< SharedLibrary > library,
                 std::unique_ptr< PluginBundle > bundle )
        : m_library( std::move( library ))
        , m_bundle( std::move( bundle ))
        , m_isValid( library != nullptr && bundle != nullptr )
    {

    }

    inline SharedLibrary * library() const
    {
        return m_library.get();
    }

    inline PluginBundle * bundle() const
    {
        return m_bundle.get();
    }

    inline bool isValid() const
    {
        return m_isValid;
    }

private:
    std::unique_ptr< SharedLibrary > m_library;

    std::unique_ptr< PluginBundle > m_bundle;

    bool m_isValid;
};


BundleLibrary::BundleLibrary()
    : m_impl( std::make_unique< BundleLibrary::Impl >() )
{

}

BundleLibrary::BundleLibrary( std::unique_ptr< SharedLibrary > library,
                              std::unique_ptr< PluginBundle > bundle )
    : m_impl( std::make_unique< BundleLibrary::Impl >(
                  std::move( library ),
                  std::move( bundle )))
{

}


SharedLibrary * BundleLibrary::library() const
{
    return m_impl->library();
}


PluginBundle * BundleLibrary::bundle() const
{
    return m_impl->bundle();
}


bool BundleLibrary::isValid() const
{
    return m_impl->isValid();
}

}
