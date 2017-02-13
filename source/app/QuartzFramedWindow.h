#pragma once

#include <QMainWindow>

namespace Quartz {

class QuartzFramedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuartzFramedWindow( QWidget *parent = 0 );

    ~QuartzFramedWindow();

private:
};

}
