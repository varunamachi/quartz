#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QSvgRenderer>
#include <QPixmap>
#include <QApplication>

#include "WelcomePage.h"

namespace Quartz {

struct WelcomePage::Data {
    Data(QWidget *parent) : m_image() {
        QSvgRenderer renderer(
                    QStringLiteral("://resources/quartz_dull.svg"),
                    parent);
        QPainter painter(&m_image);
        renderer.render(&painter);
    }

    Data() : m_image("://resources/quartz_dull.png") {
    }

    QImage m_image;
};

WelcomePage::WelcomePage(const QString &id, QWidget *parent)
    : ContentWidget(id, tr("Quartz"), "page", parent)
    , m_data(std::make_unique<Data>())
{
    QVBoxLayout *layout = new QVBoxLayout();
    auto color = QApplication::palette().text().color();
    color.setAlpha(100);
    QLabel *label = new QLabel(tr("W E L C O M E   T O   Q U A R T Z"));
    layout->addWidget(label, Qt::AlignCenter);
    label->setStyleSheet(
        "border-radius: 3px;"
        "qproperty-alignment: AlignCenter;"
        "font-size: 32px;"
        "qproperty-wordWrap: true;"
        "color: " + color.name(QColor::HexArgb)
  );
    auto p = this->palette();
    this->setAutoFillBackground(true);
    this->setPalette(p);
    this->setLayout(layout);
}

WelcomePage::~WelcomePage()
{

}

void WelcomePage::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    auto rect = this->rect() - QMargins(15, 15, 15, 15);
    painter.drawImage(rect, m_data->m_image);
    QWidget::paintEvent(evt);
}

}
