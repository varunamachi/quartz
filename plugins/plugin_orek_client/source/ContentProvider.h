#pragma once

#include <base/content_manager/AbstractContentProvider.h>
#include <base/content_manager/ContentWidget.h>

namespace Quartz { namespace Ext { namespace Orek {

class OrekContent : public ContentWidget
{
public:
    explicit OrekContent( QWidget *parent = nullptr );

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

    static const QString     EXTENSION_ID;

    static const QString     EXTENSION_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
