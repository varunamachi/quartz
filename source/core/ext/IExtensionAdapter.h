#pragma once

#include <QString>

#include "../utils/Macros.h"
#include "Extension.h"

namespace Quartz { namespace Ext {

QZ_INTERFACE IExtensionAdapter {
    virtual const QString& extensionType() const = 0;

    virtual const QString& extensionAdapterName() const = 0;

    virtual bool handleExtension(Extension * extension) = 0;

    virtual bool finalizeExtension() = 0;

    virtual ~IExtensionAdapter() {
    }
};

}} // namespace Quartz::Ext
