
#include "AbstractTemplateProvider.h"


namespace Quartz { namespace Ext { namespace Creator {

const QString AbstractTemplateProvider::EXTENSION_TYPE{"qz.template"};

AbstractTemplateProvider::AbstractTemplateProvider(
        const QString &extID,
        const QString &extName)
    : Extension(extID, extName, EXTENSION_TYPE)
{

}

AbstractTemplateProvider::~AbstractTemplateProvider()
{

}

} } }
