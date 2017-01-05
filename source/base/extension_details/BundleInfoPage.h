#pragma once

#include "../content_manager/ContentWidget.h"

namespace Quartz {

class BundleInfoPage : public ContentWidget
{
    Q_OBJECT

public:
    explicit BundleInfoPage( QWidget *parent = nullptr );

    ~BundleInfoPage();

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};


}
