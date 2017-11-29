#include <QTextStream>
#include <QMouseEvent>

#include "IdButton.h"

namespace Quartz {

IdButton::IdButton( QString id,
                    QString text,
                    int height,
                    int width,
                    QWidget *parent,
                    Qt::Orientation orientation )
    : OrientationButton( text, parent )
    , m_id( id )
    , m_dim( width, height )
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
                 "QPushButton:hover {"
                 "     background-color: #FFA858;"
                 "     color: #202020;"
                 " }"
                  ;
    setFlat( true );
    qssStream.flush();
    setStyleSheet( qss );
    setText( text );
    this->setOrientation( orientation );
}

QSize IdButton::originalSizeHint() const
{
    return m_dim;
}


void IdButton::mouseReleaseEvent( QMouseEvent *evt )
{
    QPushButton::mousePressEvent( evt );
    emit activated( m_id );
    evt->ignore();
}


}
