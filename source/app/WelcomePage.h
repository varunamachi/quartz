#pragma once

#include <base/content_manager/ContentWidget.h>

namespace Quartz {

class WelcomePage : public ContentWidget {
    Q_OBJECT
public:
    explicit WelcomePage(const QString& id, QWidget* parent = nullptr);

    virtual ~WelcomePage() override;

protected:
    void paintEvent(QPaintEvent* evt) override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
