#pragma once

#include <memory>

#include "../VQ.h"
#include "../VQCommon.h"

class std::string;
class std::stringList;
template <typename T> class QList;

namespace Vam {

class AbstractPlugin;

class PluginBundle
{
public:
    PluginBundle( const std::string &bundleId,
                  const std::string &bundleName );

    PluginBundle( PluginBundle &other ) = delete;

    PluginBundle & operator=( PluginBundle &other ) = delete;

    const std::string & bundleId() const;

    const std::string & bundleName() const;

    virtual void addPlugin( std::shared_ptr< AbstractPlugin > plugin );

    int pluginCount() const;

    AbstractPlugin * pluginAt( const int index ) const;

    virtual void addDependency( const std::string &bundleId );

    const std::stringList & dependencies() const;

    virtual ~PluginBundle();

protected:
    QList< std::shared_ptr< AbstractPlugin >> & mutablePluginList();

    std::stringList & mutalbleDependencyList();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};


}


struct VQ_CORE_EXPORT BundleWrapper {
    Vam::PluginBundle *theBundle;

};
