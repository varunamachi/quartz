
#include <QApplication>
#include <QMainWindow>

#include "ScintillaEdit.h"


int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    ScintillaEdit editor;
    editor.setMultipleSelection(true);
    editor.show();
    return app.exec();
}
