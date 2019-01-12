#pragma once

#include <memory>


#include <core/ext/Extension.h>

namespace Quartz {

class Template;

namespace Ext { namespace Creator {

class AbstractTemplateProvider : public Extension
{
public:
    AbstractTemplateProvider(const QString &extensionID,
                             const QString &extensionName);

    ~AbstractTemplateProvider();

    virtual QList<std::shared_ptr<Template>> templates() const = 0;

    static const QString EXTENSION_TYPE;


private:
};

} } }
