#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

class QWidget;
class QString;

namespace Quartz {

class Msg;
enum class NotificationType : int;

class QUARTZ_BASE_API NotificationService : public QWidget {
public:
    NotificationService(QWidget* parent);

    ~NotificationService() override;

    void info(const QString& msg);

    void warn(const QString& msg);

    void error(const QString& msg);

    void refresh();

    void add(NotificationType type, const QString& msg);

    void clear();

public Q_SLOTS:
    void reposition();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
