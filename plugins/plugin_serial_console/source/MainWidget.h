#pragma once

#include <memory>

#include <base/content_manager/ContentWidget.h>

namespace Quartz { namespace Ext { namespace SerialConsole {

class MainWidget : public ContentWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent = nullptr);

    ~MainWidget();

    static const QString CONTENT_ID;

    static const QString CONTENT_NAME;

    static const QString CONTENT_KIND;

public slots:
    void createNewConnection();

    void disconnectAll();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}}} // namespace Quartz::Ext::SerialConsole
