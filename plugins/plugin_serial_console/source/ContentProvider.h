#pragma once

#include <base/content_manager/AbstractContentProvider.h>

namespace Quartz { namespace Ext { namespace SerialConsole {

class ContentProvider : public AbstractContentProvider {

public:
    ContentProvider();

    ~ContentProvider();

    bool init() override;

    bool destroy() override;

    QVector<ContentWidget*> widgets() override;

    static const QString EXTENSION_ID;

    static const QString EXTENSION_NAME;
};

}}} // namespace Quartz::Ext::SerialConsole
