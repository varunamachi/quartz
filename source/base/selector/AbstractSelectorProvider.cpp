
#include "AbstractSelectorProvider.h"

namespace Quartz {

const QString AbstractSelectorProvider::EXTENSION_TYPE{"qz.selector"};

AbstractSelectorProvider::AbstractSelectorProvider(const QString& extensionId,
                                                   const QString& extensionName)
    : Ext::Extension(extensionId, extensionName, EXTENSION_TYPE) {
}

AbstractSelectorProvider::~AbstractSelectorProvider() {
}

} // namespace Quartz
