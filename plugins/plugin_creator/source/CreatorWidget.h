#pragma once

#include <base/content_manager/ContentWidget.h>

class Template;

namespace Quartz { namespace Ext { namespace Creator {

class TemplateManager;

class CreatorWidget : public ContentWidget
{
    Q_OBJECT

public:
    explicit CreatorWidget(std::shared_ptr<TemplateManager> tman,
                           QWidget *parent = nullptr);

    ~CreatorWidget();

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;

public slots:
    void onBrowse();

    void onCreate();

    void autoPopulate(const QString &fqid);

    void addTemplates() ;

private:

    struct Data;
    std::unique_ptr<Data> m_data;

};


} } }
