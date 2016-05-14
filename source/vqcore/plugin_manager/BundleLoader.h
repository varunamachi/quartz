#pragma once

#include <memory>

#include "PluginBundle.h"

namespace Vam {


class BundleLoader
{
public:
    QHash< QString, BundleLibrary::Ptr > loadAll( const QString & location );

    BundleLibrary::Ptr loadFile( const QString &filePath );

private:

};

}
