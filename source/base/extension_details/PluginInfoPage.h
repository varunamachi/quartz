#pragma once

#include "../QuartzBase.h"
#include "../content_manager/ContentWidget.h"

namespace Quartz { namespace Ext {

class Plugin;

class QUARTZ_BASE_API PluginInfoPage : public ContentWidget
{
    Q_OBJECT

public:
    explicit PluginInfoPage(QWidget *parent = nullptr);

    ~PluginInfoPage();

    void setPlugin(const Plugin *plugin);

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

} }
