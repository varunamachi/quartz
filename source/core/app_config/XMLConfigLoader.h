#pragma once

#include "IConfigBatchLoader.h"

namespace Quartz {

class XMLConfigLoader : public IConfigBatchLoader
{
public:
    QHash<QString, QVariant> load( const QString &path );
};







}
