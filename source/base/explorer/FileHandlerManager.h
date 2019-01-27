#pragma once

#include <memory>

#include "../content_manager/ContentWidget.h"
#include "../QuartzBase.h"

namespace Quartz {

class AbstractFileHandler;

class QUARTZ_BASE_API FileHandlerManager : public ContentWidget
{
    Q_OBJECT

public:
    explicit FileHandlerManager(QWidget *parent = nullptr);

    ~FileHandlerManager();

    void addHandler(std::shared_ptr<AbstractFileHandler> handler);

    static const QString CONTENT_ID;
    static const QString CONTENT_NAME;
    static const QString CONTENT_KIND;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
