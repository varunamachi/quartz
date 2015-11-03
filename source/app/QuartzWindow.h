#pragma once

#include <QMainWindow>

namespace Vam { namespace Quartz {

class PageManager;
class ActionBar;

class QuartzWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QuartzWindow( QWidget *parent = nullptr );

private:
    QString createStylesheet();


//    ComponentManager *m_componentManager;

//    ActionBar *m_actionBar;

};

} }
