#pragma once

#include <memory>

#include "../QuartzCore.h"

class QString;

namespace Quartz {

class QUARTZ_CORE_API BundleEnv
{
public:
    BundleEnv( const QString &bundlePath,
               const QString &bundleLibName,
               const QString &platformVersion );

    ~BundleEnv();

    const QString & bundlePath() const;

    const QString & bundleLibName() const;

    const QString & platformVersion() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
