#pragma once

#include <memory>

#include "../content_manager/ContentWidget.h"

namespace Quartz {

class BasicConfigPage : public ContentWidget
{
public:
    BasicConfigPage( const QString &id,
                     const QString &name,
                     const QString &kind,
                     QWidget *parent = nullptr );

    ~BasicConfigPage();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


}
