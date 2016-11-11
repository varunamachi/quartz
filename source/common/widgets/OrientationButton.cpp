/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** orientationbutton.cpp
** This is an extended version of Qt's QPushButton. In addition to
** QPushButton's functionality, this button's orientation can be changed
** to vertical and the button can also be mirrored.
**
** Author:	J-P Nurmi
** Date:	23th September 2006
** -------------------------------------------------------------------------
**
** // Modified for Tanyatu by Varuna L Amachi, 2013 /////////////////////// */

#include <QStylePainter>
#include <QMenu>

#include "OrientationButton.h"


namespace Quartz {


OrientationButton::OrientationButton( QWidget* parent )
        : QPushButton(parent)
{
    init();
}


OrientationButton::OrientationButton( const QString& text,
                                      QWidget* parent)
    : QPushButton( text, parent )
{
    init();
}


OrientationButton::OrientationButton( const QIcon &icon,
                                      const QString &text,
                                      QWidget *parent )
    : QPushButton( icon, text, parent )
{
    init();
}


OrientationButton::~OrientationButton()
{
}


void OrientationButton::init()
{
    m_orientation = Qt::Horizontal;
    m_mirrored = false;
}


Qt::Orientation OrientationButton::orientation() const
{
    return m_orientation;
}


void OrientationButton::setOrientation( Qt::Orientation orientation )
{
    m_orientation = orientation;
    switch ( orientation ) {
    case Qt::Horizontal:
        setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );
        break;

    case Qt::Vertical:
        setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Minimum );
        break;
    }
}


bool OrientationButton::mirrored() const
{
    return m_mirrored;
}


void OrientationButton::setMirrored( bool mirrored )
{
    m_mirrored = mirrored;
}


QSize OrientationButton::sizeHint() const
{
    QSize size = QPushButton::sizeHint();
    if ( m_orientation == Qt::Vertical ) {
        size.transpose();
    }
    return size;
}


QSize OrientationButton::minimumSizeHint() const
{
    QSize size = originalSizeHint();
    if ( m_orientation == Qt::Vertical ) {
        size.transpose();
    }
    return size;
}


void OrientationButton::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );
    QStylePainter p( this );
    switch( m_orientation )
    {
    case Qt::Horizontal:
        if( m_mirrored ) {
            p.rotate(180);
            p.translate( - width(), - height() );
        }
        break;
    case Qt::Vertical:
        if( m_mirrored ) {
            p.rotate( -90 );
            p.translate( -height(), 0 );
        }
        else {
            p.rotate( 90 );
            p.translate( 0, -width() );
        }
        break;
    }
    p.drawControl( QStyle::CE_PushButton, getStyleOption() );
}

QSize OrientationButton::originalSizeHint() const
{
    return QPushButton::minimumSizeHint();
}


QStyleOptionButton OrientationButton::getStyleOption() const
{
    QStyleOptionButton opt;
    opt.initFrom(this);
    if( m_orientation == Qt::Vertical ) {
        QSize size = opt.rect.size();
        size.transpose();
        opt.rect.setSize(size);
    }
    opt.features = QStyleOptionButton::None;
    if( isFlat() ) {
        opt.features |= QStyleOptionButton::Flat;
    }
    if( menu() ) {
        opt.features |= QStyleOptionButton::HasMenu;
    }
    if( autoDefault() || isDefault() ) {
        opt.features |= QStyleOptionButton::AutoDefaultButton;
    }
    if( isDefault() ) {
        opt.features |= QStyleOptionButton::DefaultButton;
    }
    if( isDown() || (menu() && menu()->isVisible() )) {
        opt.state |= QStyle::State_Sunken;
    }
    if( isChecked() ) {
        opt.state |= QStyle::State_On;
    }
    if( ! isFlat() && ! isDown() ) {
        opt.state |= QStyle::State_Raised;
    }
    opt.text = text();
    opt.icon = icon();
    opt.iconSize = iconSize();
    return opt;
}

}
