#pragma once

#include <memory>

#include <QWidget>

class QMainWindow;

namespace Quartz {

class TitleBar;


class QzMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QzMainWidget(bool drawWindowControls, QMainWindow *parent = 0);

    ~QzMainWidget();

    TitleBar * titleBar();

public slots:
    void onAboutToQuit();

    void setRoundedRect(bool useRoundedRect);

protected:
    struct Data;
    std::unique_ptr<Data> m_data;

    void paintEvent(QPaintEvent *event);


};

}

