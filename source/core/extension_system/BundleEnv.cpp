#include <QString>

#include "BundleEnv.h"

namespace Quartz {

struct BundleEnv::Data
{
    Data( const QString &bundlePath,
          const QString &bundleLibName,
          const QString &platformVersion )
        : m_bundlePath( bundlePath )
        , m_bundleLibName( bundleLibName )
        , m_platformVersion( platformVersion )
    {

    }

    const QString m_bundlePath;

    const QString m_bundleLibName;

    const QString m_platformVersion;
};

BundleEnv::BundleEnv( const QString &bundlePath,
                      const QString &bundleLibName,
                      const QString &platformVersion )
    : m_data{ new Data{ bundlePath, bundleLibName, platformVersion }}
{

}

BundleEnv::~BundleEnv()
{

}

const QString &BundleEnv::bundlePath() const
{
    return m_data->m_bundlePath;
}

const QString &BundleEnv::bundleLibName() const
{
    return m_data->m_bundleLibName;
}

const QString &BundleEnv::platformVersion() const
{
    return m_data->m_platformVersion;
}



}
