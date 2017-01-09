#pragma once

#include "../QuartzBase.h"
#include "../content_manager/ContentWidget.h"

namespace Quartz {

class AbstractPluginBundle;

class QUARTZ_BASE_API BundleInfoPage : public ContentWidget
{
    Q_OBJECT

public:
    explicit BundleInfoPage( QWidget *parent = nullptr );

    ~BundleInfoPage();

    void setBundle( const AbstractPluginBundle *bundle );

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};


}
