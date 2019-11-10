#pragma once

#include "../QuartzBase.h"
#include "../base/settings/AbstractConfigPage.h"

namespace Quartz { namespace Ext {

class QUARTZ_BASE_API PluginConfigPage : public AbstractConfigPage {
    Q_OBJECT

public:
    PluginConfigPage(QWidget* parent = nullptr);

    ~PluginConfigPage() override;

    bool apply() override;

    bool setDefaults() override;

    static const QString CONFIG_PAGE_ID;

    static const QString CONFIG_PAGE_NAME;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Ext
