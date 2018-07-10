#include <QTextStream>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

#include "../iconstore/IconFontStore.h"

#include "IdButton.h"

namespace Quartz {



IdButton::IdButton( QString id,
                    QString text,
                    int height,
                    int width,
                    QWidget *parent)
    : QToolButton (parent)
    , m_id( id )
    , m_dim( width, height )
{
    this->setStyle(width, height, false);
    this->setText(text);
}

IdButton::IdButton( QString id,
                    QString text,
                    int height,
                    int width,
                    const QIcon &icon,
                    bool textBelowIcon,
                    QWidget *parent)
    : QToolButton (parent)
    , m_id( id )
    , m_dim( width, height )
{
    this->setIcon(icon);
    this->setText(text);
    if (textBelowIcon) {
        this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QFontMetrics fm(this->font());
        auto h = height - fm.height() - 4;
        this->setIconSize({ h, h});
    } else {
        this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
    this->setStyle(width, height, textBelowIcon);
}

void IdButton::setStyle(int width, int height, bool big) {
    setCheckable( true );
    QString qss;
    QTextStream qssStream;
    qssStream.setString(&qss);
    auto txtColor = QApplication::palette().color(QPalette::Text);
    auto bgColor = QApplication::palette().color(QPalette::Background);
    auto selBg = txtColor;
    auto hvBg = txtColor;
    selBg.setAlpha(50);
    hvBg.setAlpha(15);
    qssStream << " QToolButton {"
                 "     border-radius: 5px;"
                 "     background-color: " << bgColor.name() << ";"
                 "     color: " << txtColor.name() << ";"
                 "     max-width: " << width << "px;"
                 "     min-width: " << width << "px;"
                 "     max-height: " << height << "px;"
                 "     min-height: " << height << "px;"
                 "     font-size: " << (big ? 9 : 12) << "px;"
                 "     padding: 0px;"
                 " }"
                 " QToolButton:checked {"
                 "     background-color: " << selBg.name(QColor::HexArgb) << ";"
                 "     color: " << txtColor.name(QColor::HexArgb) << ";"
                 " }"
                 "QToolButton:hover {"
                 "     background-color: " << hvBg.name(QColor::HexArgb) << ";"
                 "     color: " << txtColor.name(QColor::HexArgb) << ";"
                 " }"
                  ;
    qssStream.flush();
    setStyleSheet( qss );
    setContentsMargins(0, 10, 0, 10);
}

QSize IdButton::sizeHint() const
{
    return m_dim;
}


void IdButton::mouseReleaseEvent( QMouseEvent *evt )
{
    QToolButton::mousePressEvent( evt );
    emit activated( m_id );
    evt->ignore();
}


}
