
#pragma once

#include <base/content_manager/AbstractContentProvider.h>

namespace Quartz { namespace Ext { namespace IconFontExplorer {

class TemplateManager;

class ContentProvider : public AbstractContentProvider {
public:
    explicit ContentProvider();

    ~ContentProvider();

    bool init() override;

    bool destroy() override;

    QVector<ContentWidget*> widgets() override;

    static const QString EXTENSION_ID;

    static const QString EXTENSION_NAME;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}}} // namespace Quartz::Ext::IconFontExplorer
