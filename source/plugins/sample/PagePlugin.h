#pragma once

#include <memory>

#include <quartz_core/IQuartzPlugin.h>
#include <quartz_core/IQuartzPageManager.h>

namespace Vam {

class SamplePage : public Quartz::QuartzPage
{
    Q_OBJECT
public:
    SamplePage( const QString &pageId,
                const QString &category,
                const QString &categoryName,
                const QString &displayName,
                QWidget *parent = nullptr );
};

class PagePlugin : public Quartz::IQuartzPlugin
{

public:
    QString pluginId() const;

    bool init( Quartz::QuartzContext &context );

    bool uninit( Quartz::QuartzContext &context );

    const static QString PLUGIN_ID;

private:
    std::unique_ptr< SamplePage > m_samplePage;
};


}

