#pragma once

#include <base/content_manager/AbstractContentProvider.h>
#include <base/content_manager/ContentWidget.h>

namespace Quartz { namespace Plugin { namespace Creator {

class Content : public ContentWidget
{
public:
    explicit Content( QWidget *parent = nullptr );

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;
};

class ContentProvider : public AbstractContentProvider
{
public:
    ContentProvider();

    ~ContentProvider();

    bool init() override;

    bool destroy() override;

    QVector< ContentWidget *> widgets() override;

    static const QString     PLUGIN_ID;

    static const QString     PLUGIN_NAME;
};

} } }