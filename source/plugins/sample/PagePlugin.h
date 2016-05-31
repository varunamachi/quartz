#pragma once

#include <memory>

#include <quartz_core/IQuartzPlugin.h>
#include <quartz_core/IQuartzPageManager.h>

namespace Vq {

class SamplePage : public Quartz::QuartzPage
{
    Q_OBJECT
public:
    SamplePage( QWidget *parent = nullptr );

    const static QString PAGE_ID;
    const static QString PAGE_CATEGORY;
    const static QString PAGE_CATEGORY_NAME;
    const static QString PAGE_DISPLAY_NAME;
};

class PagePlugin : public Quartz::IQuartzPlugin
{

public:
    QString pluginId() const;

    Result< bool > init( Quartz::QuartzContext &context );

    Result< bool > uninit( Quartz::QuartzContext &context );

    const static QString PLUGIN_ID;

private:
    std::unique_ptr< SamplePage > m_samplePage;
};


}

