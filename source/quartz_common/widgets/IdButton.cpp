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
                 "     min-width: " << width << "px;"
                 "     min-height: " << height << "px;"
                 "     font-size: 10px;"
                 " }"
                 " QPushButton:checked {"
                 "     background-color: #FFA858;"
                 "     color: #202020;"
                 " }";
    setStyleSheet( qss );
    setText( text );
}


void IdButton::mousePressEvent( QMouseEvent *evt )
{
    if( ! isChecked() ) {
        QPushButton::mousePressEvent( evt );
        emit activated( m_id );
    }
    evt->ignore();
}

} }
