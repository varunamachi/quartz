
#include <QHBoxLayout>

#include "QzMainWidget.h"
#include "QuartzFramedWindow.h"

namespace Quartz {

QuartzFramedWindow::QuartzFramedWindow( QWidget *parent )
    : QMainWindow{ parent }
{
    this->setCentralWidget( new QzMainWidget{ this });

}

QuartzFramedWindow::~QuartzFramedWindow()
{
}

}
