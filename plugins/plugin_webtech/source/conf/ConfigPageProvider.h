#pragma once

#include <base/settings/AbstractConfigPageProvider.h>

namespace Quartz { namespace Ext { namespace WebTech {

class ConfigPageProvider : public AbstractConfigPageProvider {
public:
    ConfigPageProvider();

    ~ConfigPageProvider();

    QVector<AbstractConfigPage*> configPages() const;

    static const QString PLUGIN_ID;
    static const QString PLUGIN_NAME;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}}} // namespace Quartz::Ext::WebTech
