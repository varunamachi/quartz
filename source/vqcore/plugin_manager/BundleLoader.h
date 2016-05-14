#pragma once

#include <memory>

class QString;

namespace Vam {

class BundleLibrary;

class BundleLoader
{
public:
    QHash< QString, BundleLibrary::Ptr > loadAll( const QString & location );

    std::shared_ptr< BundleLibrary > loadFile( const QString &filePath );

private:

};

}
