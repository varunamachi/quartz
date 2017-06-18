#pragma once

#include <base/content_manager/AbstractContentProvider.h>

namespace Quartz { namespace Plugin { namespace Creator {

class TemplateManager;

class ContentProvider : public AbstractContentProvider
{
public:
    explicit ContentProvider( std::shared_ptr< TemplateManager > tman );

    ~ContentProvider();

    bool init() override;

    bool destroy() override;

    QVector< ContentWidget *> widgets() override;

    static const QString     PLUGIN_ID;

    static const QString     PLUGIN_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
