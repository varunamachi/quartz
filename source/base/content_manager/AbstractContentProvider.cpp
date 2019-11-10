
#include "AbstractContentProvider.h"

namespace Quartz {

const QString AbstractContentProvider::EXTENSION_TYPE{"qz.content"};

AbstractContentProvider::AbstractContentProvider(const QString& extensionId,
                                                 const QString& extensionName)
    : Ext::Extension(extensionId, extensionName, EXTENSION_TYPE) {
}

AbstractContentProvider::~AbstractContentProvider() {
}

} // namespace Quartz
