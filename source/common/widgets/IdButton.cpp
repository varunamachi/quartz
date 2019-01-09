#include <QTextStream>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

#include "../iconstore/IconFontStore.h"

#include "IdButton.h"

namespace Quartz {

struct IdButton::Data {
    Data(const QString &id,
         const QSize &dim,
         const QIcon &icon,
         const QIcon &activeIcon)
        : m_id(id)
        , m_dim(dim)
        , m_icon(icon)
        , m_activeIcon(activeIcon)
    {

    }

    QString m_id;

    QSize m_dim;

    QIcon m_icon;

    QIcon m_activeIcon;
};



IdButton::IdButton( QString id,
                    QString text,
                    int height,
                    int width,
                    QWidget *parent)
    : m_data(std::make_unique<Data>(
                 id,
                 QSize{width, height},
                 QIcon{},
                 QIcon{}))
    , QToolButton (parent)


{
    this->setStyle(width, height, false);
    this->setText(text);
}

IdButton::IdButton( QString id,
                    QString text,
                    int height,
                    int width,
                    const QIcon &icon,
                    const QIcon &activeIcon,
                    bool textBelowIcon,
                    QWidget *parent)
    : m_data(std::make_unique<Data>(
                 id,
                 QSize{width, height},
                 icon,
                 activeIcon))
    , QToolButton (parent)

{
    this->setIcon(icon);
    this->setText(text);
    if (textBelowIcon) {
//        this->setToolButtonStyle(Qt::ToolButtonIconOnly);
        this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QFontMetrics fm(this->font());
        auto h = height - fm.height() - 4;
        this->setIconSize({ h, h});
    } else {
        this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
    this->setStyle(width, height, textBelowIcon);
    QObject::connect(
                this,
                &QAbstractButton::toggled,
                [this](bool checked) {
        this->setIcon(checked ? m_data->m_activeIcon : m_data->m_icon);
    });
}

IdButton::~IdButton()
{

}

void IdButton::setStyle(int width, int height, bool big) {
    setCheckable( true );
    QString qss;
    QTextStream qssStream;
    qssStream.setString(&qss);
    auto txtColor = QApplication::palette().color(QPalette::Text);
    auto hlTxtColor = QApplication::palette().color(QPalette::Highlight);
    auto hlBg = QApplication::palette().color(QPalette::Highlight);
    auto hlBd = hlTxtColor;
    auto selBg = txtColor;
    auto hvBg = txtColor;
    txtColor.setAlpha(200);
    selBg.setAlpha(80);
    hvBg.setAlpha(30);
    hlBg.setAlpha(60);
    hlBd.setAlpha(150);
    setContentsMargins({0, 5, 0, 5});

    auto fontSize = (big ? 10 : 12);
    qssStream << " QToolButton {"
//                 "     border-radius: 5px;"
                 "     max-width: " << width << "px;"
                 "     min-width: " << width << "px;"
                 "     max-height: " << height << "px;"
                 "     min-height: " << height << "px;"
                 "     font-size: " << fontSize << "px;"
//                 "     padding-bottom: 5px;"
//                 "     padding-top: 5px;"
                 "     border: none;"
                 " }"
                 " QToolButton:checked {"
                 "     background-color: " << hlBg.name(QColor::HexArgb) << ";"
                 "     border-color: " << hlBg.name(QColor::HexArgb) << ";"
                 "     color: " << hlTxtColor.name(QColor::HexArgb) << ";"
                 "     border-width: 2px;"
                 "     border: solid;"
                 " }"
                 "QToolButton:hover {"
                 "     background-color: " << hvBg.name(QColor::HexArgb) << ";"
//                 "     color: " << txtColor.name(QColor::HexArgb) << ";"
                 " }"
                  ;
    qssStream.flush();
    setStyleSheet( qss );
    setContentsMargins(0, 10, 0, 10);
}

QSize IdButton::sizeHint() const
{
    return m_data->m_dim;
}


void IdButton::mouseReleaseEvent(QMouseEvent *evt)
{
    QToolButton::mousePressEvent(evt);
    emit activated(m_data->m_id);
    evt->ignore();
}


}
