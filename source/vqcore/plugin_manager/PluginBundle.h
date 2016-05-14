#pragma once

#include <memory>

#include "../VQ.h"
#include "../VQCommon.h"

class QString;
class QStringList;
template <typename T> class QList;

namespace Vam {

class AbstractPlugin;

class PluginBundle
{
public:
    PluginBundle( const QString &bundleId,
                  const QString &bundleName );

    PluginBundle( PluginBundle &other ) = delete;

    PluginBundle & operator=( PluginBundle &other ) = delete;

    const QString & bundleId() const;

    const QString & bundleName() const;

    virtual void addPlugin( std::shared_ptr< AbstractPlugin > plugin );

    int pluginCount() const;

    AbstractPlugin * pluginAt( const int index ) const;

    virtual void addDependency( const QString &bundleId );

    const QStringList & dependencies() const;

    virtual ~PluginBundle();

protected:
    QList< std::shared_ptr< AbstractPlugin >> & mutablePluginList();

    QStringList & mutalbleDependencyList();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};


}


struct VQ_CORE_EXPORT BundleWrapper {
    Vam::PluginBundle *theBundle;

};
