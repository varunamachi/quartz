#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class QUARTZ_BASE_API QuartzItem : public QWidget {
    Q_OBJECT
public:
    QuartzItem(const QString& itemId,
               const QString& category,
               QWidget* widget = nullptr);

    ~QuartzItem();

    const QString itemId() const;

    const QString itemCategory() const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
