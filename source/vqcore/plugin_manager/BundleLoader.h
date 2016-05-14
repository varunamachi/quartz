#pragma once

#include <memory>

#include <quartz_core/PluginBundle.h>

namespace Vam { namespace Quartz {

class BundleLibrary
{
public:
    using Ptr = std::shared_ptr< BundleLibrary >;

    BundleLibrary()
        : m_library( nullptr )
        , m_bundle( nullptr )
        , m_isValid( false )
    {

    }

    BundleLibrary( QLibrary *library,
                   PluginBundle *bundle )
        : m_library( library )
        , m_bundle( bundle )
        , m_isValid( library != nullptr && bundle != nullptr )
    {

    }

    QLibrary & library() const
    {
        return *m_library;
    }

    PluginBundle & bundle() const
    {
        return *m_bundle;
    }

    bool isValid() const
    {
        return m_isValid;
    }

private:

    QLibrary *m_library;

    PluginBundle *m_bundle;

    bool m_isValid;
};


class BundleLoader
{
public:
    QHash< QString, BundleLibrary::Ptr > loadAll( const QString & location );

    BundleLibrary::Ptr loadFile( const QString &filePath );

private:

};

} }
