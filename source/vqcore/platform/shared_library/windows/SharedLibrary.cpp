
#include <windows.h>

#include "../../../logger/Logging.h"
#include "../SharedLibrary.h"

namespace Vq {

class SharedLibrary::Impl
{
public:
    explicit Impl( const std::string & libPath )
        : m_libPath( libPath )
        , m_handle( nullptr )
    {

    }


    Result< bool > load()
    {
        if( m_handle != nullptr ) {
            VQ_WARN( "Vq:Core" ) << "DLL at " << m_libPath << " is already "
                                    "loaded";
            return R::success( true );
        }

        auto result = R::success( true );
        HINSTANCE handle = LoadLibrary( m_libPath.c_str() );
        if( handle == nullptr ) {
            auto result = R::stream( false, VQ_TO_ERR( ::GetLastError() ))
                    << "Failed to load DLL at " << m_libPath
                    << R::fail;
            VQ_ERROR( "Vq:Core" ) << result;
        }
        else {
            VQ_DEBUG( "Vq::Core" )
                    << "Loaded DLL from " << m_libPath;
        }
        return result;
    }


    Result< bool > unload()
    {
        if( m_handle == nullptr ) {
            VQ_WARN( "Vq:Core" ) << "DLL at " << m_libPath
                                 << " is not loaded";
            return R::success( false );
        }
        auto result = R::success( false );
        auto retCode = FreeLibrary( m_handle );
        if( retCode == 0 ) {
            result = R::stream( false, VQ_TO_ERR( ::GetLastError() ))
                    << "Failed to unload DLL at " << m_libPath << R::fail;
            VQ_ERROR( "Vq:Core" ) << result;
        }
        else {
            VQ_DEBUG( "Vq:Core" ) << "DLL at " << m_libPath
                                  << " unloaded successfully";
        }
        return result;
    }


    Result< LibraryFunction > resolve(
            const std::string &symbolName )
    {
        if( m_handle == nullptr ) {
            auto result = R::stream( LibraryFunction{ nullptr } )
                    << "Failed to resolve symbol " << symbolName
                    << " in DLL at " << m_libPath << " - invalid DLL handle"
                    << R::fail;
            VQ_ERROR( "Vq:Core" ) << result;
            return result;
        }
        auto procAddr = GetProcAddress( m_handle, symbolName.c_str() );

        if( procAddr == nullptr ) {
             auto result = R::stream( LibraryFunction{ nullptr },
                                      VQ_TO_ERR( ::GetLastError() ))
                     << "Failed to resolve symbol " << symbolName
                     << " in DLL at " << m_libPath << R::fail;
            VQ_ERROR( "Vq:Core" ) << result;
            return result;
        }

        auto address = reinterpret_cast< void * >( procAddr );
        VQ_DEBUG( "Vq:Core" ) << "Resolved symbol " << symbolName
                              << " in DLL at " << m_libPath;
        return R::success( LibraryFunction{ address });
    }

    ~Impl() {
        if( m_handle != nullptr ) {
            unload();
        }
    }

private:
    std::string m_libPath;

    HINSTANCE m_handle;
};



//---------------------- Interface
SharedLibrary::SharedLibrary( const std::string & libPath )
    : m_impl( std::make_unique< Impl >( libPath ))
{

}


SharedLibrary::~SharedLibrary()
{

}


Result< bool > SharedLibrary::load()
{
    return m_impl->load();
}


Result< bool > SharedLibrary::unload()
{
    return m_impl->unload();
}


Result< LibraryFunction > SharedLibrary::resolve(
        const std::string &symbolName )
{
    return m_impl->resolve( symbolName );
}


}
