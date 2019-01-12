#pragma once

#include <memory>

#include <QMainWindow>

namespace Quartz {

class QzMainWidget;

class QuartzFramelessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuartzFramelessWindow(QWidget *parent = 0);

    ~QuartzFramelessWindow();

    void mouseMove(QPoint newPos, QPoint oldPos);

private slots:
    void onMaximizeRestore();

    void onMinimize();

protected:
    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void showEvent(QShowEvent *evt);

    void resizeEvent(QResizeEvent *evt);

private:
    struct Data;
    std::unique_ptr<Data> m_data;

    void maximize();

    void restore();

    void minimize();
};

}
