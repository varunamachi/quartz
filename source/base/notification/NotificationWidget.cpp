#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>

#include <common/iconstore/IconFontStore.h>

#include "Msg.h"
#include "NotificationWidget.h"

namespace Quartz {

const auto ICON_SIZE = QSize{32, 32};
const auto COL_INF = QColor{24, 122, 220};
const auto COL_WRN = QColor{179, 143, 0};
const auto COL_ERR = QColor{204, 41, 0};

const QPixmap & icon(NotificationType type) {
    if (type == NotificationType::Info) {
        static auto INFO = getIcon(MatIcon::InfoOutline,
                                   COL_INF).pixmap(ICON_SIZE);
        return INFO;
    } else if(type == NotificationType::Warning) {
        static auto WARN = getIcon(MatIcon::Warning, COL_WRN).pixmap(ICON_SIZE);
        return WARN;
    }
    static auto ERR  = getIcon(MatIcon::Error, COL_ERR).pixmap(ICON_SIZE);
    return ERR;
}

struct NotificationWidget::Data
{
    Data(std::shared_ptr<Msg> &&msg,
         NotificationWidget * /*widget*/)
        : m_msg(msg)
    {

    }

    std::shared_ptr<Msg> m_msg;

};


NotificationWidget::NotificationWidget(
        std::shared_ptr<Msg> msg,
        QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(std::move(msg), this))
{
    auto label = new QLabel(this);
    label->setWordWrap(true);
//    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    label->setText(m_data->m_msg->text());
    auto icn = new QLabel(this);
    icn->setPixmap(icon(m_data->m_msg->type()));
    icn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    auto closeBtn = new QPushButton(getIcon(FAIcon::Times), "", this);
    auto ml = new QHBoxLayout();
    ml->addWidget(icn);
    ml->addWidget(label);
    ml->addWidget(closeBtn);
    ml->setSizeConstraint(QLayout::SetMinimumSize);

//    this->setStyleSheet("border-style: solid; "
//                        "border-width: 1px;"
//                        "border-color: yellow;");

    ml->setAlignment(icn, Qt::AlignLeft);
    ml->setAlignment(label, Qt::AlignLeft);
    ml->setAlignment(closeBtn, Qt::AlignRight | Qt::AlignTop);
    ml->setStretch(0, 0);
    ml->setStretch(1, 1);
    ml->setStretch(2, 0);
    this->setLayout(ml);
//    this->setMinimumHeight(10);
    this->setFixedWidth(300);
    connect(closeBtn,
            &QPushButton::released,
            this,
            &NotificationWidget::closed);
    this->setLayout(ml);
}

NotificationWidget::~NotificationWidget()
{

}

const Msg* NotificationWidget::msg() const
{
    return m_data->m_msg.get();
}

void NotificationWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter{this};
    QColor col;
    switch (m_data->m_msg->type()) {
    case NotificationType::Info: col = COL_INF; break;
    case NotificationType::Warning: col = COL_WRN; break;
    case NotificationType::Error: col = COL_ERR; break;
    }
    auto rect = event->rect();
    painter.fillRect(rect, this->palette().window());
    painter.setPen(col);
    painter.drawRect(rect.x()      + 1,
                     rect.y()      + 1,
                     rect.width()  - 2,
                     rect.height() - 2 );

}

}


