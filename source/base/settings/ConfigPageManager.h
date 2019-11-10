#pragma once

#include <memory>

#include "../QuartzBase.h"
#include "../content_manager/ContentWidget.h"

namespace Quartz {

class AbstractConfigPage;

class QUARTZ_BASE_API ConfigPageManager : public ContentWidget {
    Q_OBJECT

public:
    ConfigPageManager(QWidget* parent = nullptr);

    ~ConfigPageManager();

    bool addPage(AbstractConfigPage* page);

    bool removePage(const QString& pageId);

    AbstractConfigPage* page(const QString& pageId);

    void selectPage(const QString& pageId);

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
