
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
            return Result< bool >::success();
        }

        auto result = Result< bool >::success();
        HINSTANCE handle = LoadLibrary( m_libPath.c_str() );
        if( handle == nullptr ) {
            VQ_ERROR( "Vq:Core" )
                    << "Failed to load DLL at "
                    << m_libPath << "- Error Code: "
                    << GetLastError();
            result = Result< bool >::failure( "Failed to load DLL" );
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
            VQ_WARN( "Vq:Core" ) << "Library at " << m_libPath
                                 << " is not loaded";
            return Result< bool >::success();
        }
        auto result = Result< bool >::success();
        auto retCode = FreeLibrary( m_handle );
        if( retCode == 0 ) {
            VQ_ERROR( "Vq:Core" ) << "Failed to unload DLL at " << m_libPath
                                  << " - ErrorCode: " << GetLastError();
            result = Result< bool >::failure( "Failed to unload DLL" );
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
            VQ_ERROR( "Vq:Core" ) << "Failed to resolve symbol " << symbolName
                                  << " in DLL at " << m_libPath
                                  << " - invalid DLL handle";
            return Result< LibraryFunction >::failure(
                        LibraryFunction{ nullptr },
                        "Failed to resolve symbol - invalid DLL handle" );
        }
        auto result = Result< LibraryFunction >::failure(
                    LibraryFunction{ nullptr },
                    "Failed to find given symbol in DLL" );
        auto procAddr = GetProcAddress( m_handle, symbolName.c_str() );
        if( procAddr != nullptr ) {
            auto address = reinterpret_cast< void * >( procAddr );
            result = Result< LibraryFunction >::success(
                        LibraryFunction{ address });
            VQ_DEBUG( "Vq:Core" ) << "Resolved symbol " << symbolName
                                  << " in DLL at " << m_libPath;
        }
        else {
            VQ_ERROR( "Vq:Core" ) << "Failed to resolve symbol " << symbolName
                                  << " in DLL at " << m_libPath
                                  << " - ErrorCode: " << GetLastError();
        }
        return result;
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
