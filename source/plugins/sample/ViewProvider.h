#pragma once

#include <base/view_manager/AbstractViewProvider.h>

namespace Quartz { namespace Plugin { namespace Sample {

class ViewProvider : public AbstractViewProvider
{


    // IPlugin interface
public:
    const QString &pluginId() const override;

    const QString &pluginName() const override;

    const QStringList &dependencies() const override;

    bool init() override;

    bool destroy() override;

    QuartzView *view() const override;
};



} } }
