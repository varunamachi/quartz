#pragma once

#include <memory>

#include <QWidget>

namespace Quartz {

class QuartzPage : public QWidget
{
    Q_OBJECT
public:
    QuartzPage( const QString &pageId,
                const QString &category,
                const QString &categoryName,
                const QString &displayName,
                QWidget *parent = nullptr );

    ~QuartzPage();

    const QString & pageId() const;

    const QString & pageCategoryId() const;

    const QString & pageDisplayName() const;

    const QString & pageCategoryName() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
