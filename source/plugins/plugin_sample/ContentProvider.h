#pragma once

#include <base/content_manager/AbstractContentProvider.h>
#include <base/content_manager/ContentWidget.h>

namespace Quartz { namespace Plugin { namespace Sample {

class SampleContent : public ContentWidget
{
public:
    explicit SampleContent( QWidget *parent = nullptr );

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

    ContentWidget * widget() override;

    static const QString     PLUGIN_ID;

    static const QString     PLUGIN_NAME;

    static const QStringList DEPENDENCIES;
};

} } }