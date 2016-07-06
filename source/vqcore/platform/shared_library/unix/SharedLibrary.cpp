
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
            return R::success( true );
        }
        auto result = R::success( true );
        m_handle = dlopen( m_libPath.c_str(), RTLD_LAZY );
        if( m_handle == nullptr ) {
            result = R::stream( false, errno )
                    << "Failed to load shared object at "
                    << m_libPath << R::fail;
            VQ_ERROR( "Vq:Core" ) << result;
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
            return R::success( true );
        }
        auto result = R::success( true );
        auto code = dlclose( m_handle );
        if( code != 0 ) {
            result = R::stream( false )
                    << "Failed to unload shared object at "<< m_libPath
                    << " -- " << dlerror() << R::fail;
            VQ_ERROR( "Vq:Core" ) << result;
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
             auto result = R::stream( LibraryFunction{ nullptr } )
                     << "Failed to resolve symbol " << symbolName
                     << " in Shared Library at " << m_libPath
                     << " - invalid library handle" << R::fail;
            VQ_ERROR( "Vq:Core" ) << result;
            return result;
        }
        auto funcPtr = dlsym( m_handle, symbolName.c_str() );
        auto error = dlerror();
        if( error != nullptr || funcPtr == nullptr ) {
            auto result = R::stream( LibraryFunction{ nullptr })
                    << "Symbol with name '" << symbolName
                    << "' could not be resolved in library at " << m_libPath
                    << " -- " << error << R::fail;
            VQ_DEBUG( "Vq:Core" ) << result;
            return result;
        }
        VQ_DEBUG( "Vq:Core" ) << "Symbol with name '" << symbolName
                              << "' resolved in library at " << m_libPath;
        return R::success( LibraryFunction{ funcPtr });
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
