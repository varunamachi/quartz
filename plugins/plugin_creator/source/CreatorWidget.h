#pragma once

#include <base/content_manager/ContentWidget.h>

namespace Quartz { namespace Plugin { namespace Creator {

class CreatorWidget : public ContentWidget
{
public:
    explicit CreatorWidget( QWidget *parent = nullptr );

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;

private:

};


} } }
