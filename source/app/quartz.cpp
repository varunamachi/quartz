#include <QApplication>

#include "QuartzWindow.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    Vq::Quartz::QuartzWindow window;
    window.show();
    return app.exec();
}

