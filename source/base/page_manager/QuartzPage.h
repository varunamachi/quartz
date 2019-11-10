#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class QUARTZ_BASE_API QuartzPage : public QWidget {
    Q_OBJECT
public:
    QuartzPage(const QString& pageId,
               const QString& category,
               const QString& categoryName,
               const QString& displayName,
               QWidget* parent = nullptr);

    ~QuartzPage();

    const QString& pageId() const;

    const QString& pageCategoryId() const;

    const QString& pageDisplayName() const;

    const QString& pageCategoryName() const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
