#pragma once

#include <memory>

#include <base/settings/AbstractConfigPage.h>

namespace Quartz { namespace Ext { namespace WebTech {

class ConfigPage : public AbstractConfigPage {
    Q_OBJECT

public:
    ConfigPage(QWidget* parent = nullptr);

    ~ConfigPage() override;

    bool apply() override;

    bool setDefaults() override;

    static const QString CONFIG_PAGE_NAME;
    static const QString CONFIG_PAGE_ID;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}}} // namespace Quartz::Ext::WebTech
