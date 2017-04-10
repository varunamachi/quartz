
#include <QApplication>
#include <QMainWindow>

#include "ScintillaEdit.h"


int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    ScintillaEdit editor;
    editor.setMultipleSelection(true);
    editor.setAdditionalSelectionTyping( true );
    editor.setMultiPaste( 1 );
    editor.styleSetFont( SC_WEIGHT_NORMAL, "Consolas" );
    editor.show();
    return app.exec();
}
