#include <QTextStream>
#include <QMouseEvent>

#include "IdButton.h"

namespace Vam { namespace Quartz {

IdButton::IdButton( QString id,
                    QString text,
                    int height,
                    int width,
                    QWidget *parent )
    : QPushButton( parent )
    , m_id( id )
{
    setCheckable( true );
    QString qss;
    QTextStream qssStream;
    qssStream.setString( &qss );
    qssStream << " QPushButton {"
                 "     border-radius: 5px;"
                 "     background-color: regba( 32, 32, 32, 200 );"
                 "     max-width: " << width << "px;"
                 "     min-width: " << width << "px;"
                 "     max-height: " << height << "px;"
                 "     min-height: " << height << "px;"
                 "     font-size: 12px;"
                 "     color: white;"
                 " }"
                 " QPushButton:checked {"
                 "     background-color: #FFA858;"
                 "     color: #202020;"
                 " }"
//                 "QPushButton:hover {"
//                 "     background-color: #FFA858;"
//                 "     color: #202020;"
//                 " }"
                 ;
    qssStream.flush();
    setStyleSheet( qss );
    setText( text );
}


void IdButton::mouseReleaseEvent( QMouseEvent *evt )
{
    if( ! isChecked() ) {
        QPushButton::mousePressEvent( evt );
//        setChecked( true );
        emit activated( m_id );
    }
    evt->ignore();
//    QPushButton::mousePressEvent( evt );
}

} }
