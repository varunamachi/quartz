
#include <dlfcn.h>

#include "../../../logger/Logging.h"

#include "../SharedLibrary.h"


namespace Vq
{

class SharedLibrary::Impl
{
public:
    explicit Impl( const std::string & libPath )
        : m_libPath( libPath )
        , m_handle( nullptr )
    {

    }

    ~Impl() {
        if( m_handle != nullptr ) {
            unload();
        }
    }


    Result< bool > load()
    {
        if( m_handle != nullptr ) {
            VQ_WARN( "Vq:Core" ) << "Shared library at " << m_libPath
                                 << " is already loaded";
            return Result< bool >::success();
        }
        auto result = Result< bool >::success();
        m_handle = dlopen( m_libPath.c_str(), RTLD_LAZY );
        if( m_handle == nullptr ) {
            VQ_ERROR( "Vq:Core" ) << "Failed to load shared object at "
                                  << m_libPath << ": " << dlerror();
            result = Result< bool >::failure( "Failed to load shared object" );
        }
        else {
            VQ_INFO( "Vq:Core" ) << "Successfully loaded shared object at "
                                 << m_libPath;
        }
        return result;
    }


    Result< bool > unload()
    {
        if( m_handle == nullptr ) {
            VQ_WARN( "Vq:Core" ) << "Shared Library at " << m_libPath
                                 << " is not loaded";
            return Result< bool >::success();
        }
        auto result = Result< bool >::success();
        auto code = dlclose( m_handle );
        if( code != 0 ) {
            VQ_ERROR( "Vq:Core" ) << "Failed to unload shared object at "
                                  << m_libPath << " : " << dlerror();
            result = Result< bool >::failure( "Failed to unload shared object");
        }
        else {
            VQ_INFO( "Vq:Core" ) << "Successfully unloaded shared object at "
                                 << m_libPath;
            m_handle = nullptr;
        }
        return result;
    }


    Result< LibraryFunction > resolve(
            const std::string &symbolName )
    {
        if( m_handle == nullptr ) {
            VQ_ERROR( "Vq:Core" ) << "Failed to resolve symbol " << symbolName
                                  << " in Shared Library at " << m_libPath
                                  << " - invalid library handle";
            return Result< LibraryFunction >::failure(
                        LibraryFunction{ nullptr },
                        "Failed to resolve symbol - invalid library handle" );
        }
        auto result = Result< LibraryFunction >::failure(
                    LibraryFunction{ nullptr },
                    "Could not find the symbol" );
        auto funcPtr = dlsym( m_handle, symbolName.c_str() );
        auto error = dlerror();
        if( error == nullptr && funcPtr != nullptr ) {
            result = Result< LibraryFunction >::success(
                        LibraryFunction{ funcPtr });
            VQ_DEBUG( "Vq:Core" ) << "Symbol with name '" << symbolName
                                  << "' resolved in library at " << m_libPath;
        }
        else {
            result = Result< LibraryFunction >::failure(
                        LibraryFunction{ nullptr },
                        "Failed to resolve given symbol" );
            VQ_DEBUG( "Vq:Core" )
                    << "Symbol with name '" << symbolName
                    << "' could not be resolved in library at " << m_libPath
                    << ": " << error;
        }
        return result;
    }

private:
    std::string m_libPath;

    void *m_handle;
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
