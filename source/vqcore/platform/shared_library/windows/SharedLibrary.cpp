
#include "../SharedLibrary.h"

namespace Vam
{

class SharedLibrary::Impl
{
public:
    explicit Impl( const std::string & libPath )
        : m_libPath( libPath )
    {

    }

    Result< bool > load()
    {
        return Result< bool >::failure( "Not Implemented" );
    }

    Result< bool > unload()
    {
        return Result< bool >::failure( "Not Implemented" );
    }


    Result< SharedLibrary::LibraryFunction > resolve(
            const std::string &/*symbolName*/ )
    {
        return Result< SharedLibrary::LibraryFunction >::failure(
                    nullptr,
                    "Not Implemented" );
    }

private:
    std::string m_libPath;
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


Result< SharedLibrary::LibraryFunction > SharedLibrary::resolve(
        const std::string &symbolName )
{
    return m_impl->resolve( symbolName );
}


}
