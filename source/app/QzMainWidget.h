#pragma once

#include <memory>

#include <QWidget>

class QMainWindow;
class QResizeEvent;

namespace Quartz {

class TitleBar;

class QzMainWidget : public QWidget {
    Q_OBJECT
public:
    explicit QzMainWidget(QMainWindow* parent = nullptr);

    ~QzMainWidget() override;

public slots:
    void onAboutToQuit();

    void setRoundedRect(bool useRoundedRect);

    const TitleBar* titleBar() const;

protected:
    struct Data;
    std::unique_ptr<Data> m_data;

    void paintEvent(QPaintEvent* event) override;

    //    void resizeEvent(QResizeEvent *event) override;
};

} // namespace Quartz
