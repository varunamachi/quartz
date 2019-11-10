#pragma once

#include <QMainWindow>

namespace Quartz {

class QuartzFramedWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit QuartzFramedWindow(QWidget* parent = nullptr);

    ~QuartzFramedWindow() override;

protected:
    void moveEvent(QMoveEvent* event) override;
};

} // namespace Quartz
