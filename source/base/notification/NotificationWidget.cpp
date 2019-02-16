#include "NotificationWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <common/iconstore/IconFontStore.h>

namespace Quartz {

namespace
{
const QSize ICON_SIZE = {32, 32};

const QPixmap & icon(NotificationType type) {
    if (type == NotificationType::Info) {
        static auto INFO = getIcon(
                    MatIcon::Done, {24, 122, 220}).pixmap(ICON_SIZE);
        return INFO;
    } else if(type == NotificationType::Warning) {
        static auto WARN = getIcon(
                    MatIcon::Warning, {179, 143, 0}).pixmap(ICON_SIZE);
        return WARN;
    }
    static auto ERR  = getIcon(
                MatIcon::Error, {204, 41, 0}).pixmap(ICON_SIZE);
    return ERR;
}

//const QString ICSS =
//        "ngbox {"
//                        "   border-color: rgba(24, 122, 220, 0.5);"
//                        "   border-left-color: rgba(24, 122, 220, 0.5);"
//                        "   border-style: solid;"
//                        "   border-width: 1px;"
//                        "   border-left-width: 6px;"
//                        "   padding: 10px;"
//                        "}";
//const QString WCSS =
//        "#ngbox {"
//                        "   border-color: rgba(179, 143, 0, 0.5);"
//                        "   border-left-color: rgba(179, 143, 0, 0.5);"
//                        "   border-style: solid;"
//                        "   border-width: 1px;"
//                        "   border-left-width: 6px;"
//                        "   padding: 10px;"
//                        "}";
//const QString ECSS =
//        "#ngbox {"
//                        "   border-color: rgba(204, 41, 0, 0.5);"
//                        "   border-left-color: rgba(204, 41, 0, 0.5);"
//                        "   border-style: solid;"
//                        "   border-width: 1px;"
//                        "   border-left-width: 6px;"
//                        "   padding: 10px;"
//                        "}";
}


NotificationWidget::NotificationWidget(Msg &&msg, QWidget *parent)
    : QWidget(parent)
    , m_msg(std::move(msg))
{
    auto label = new QLabel(this);
    label->setText(m_msg.m_msg);
    label->setWordWrap(true);
    auto icn = new QLabel(this);
    icn->setPixmap(icon(m_msg.m_type));
    auto closeBtn = new QPushButton(getIcon(FAIcon::Times), "", this);
    auto ml = new QHBoxLayout();
    ml->addWidget(icn);
    ml->addWidget(label);
    ml->addWidget(closeBtn);

    ml->setAlignment(icn, Qt::AlignLeft);
    ml->setAlignment(label, Qt::AlignLeft);
    ml->setAlignment(closeBtn, Qt::AlignRight | Qt::AlignTop);
    ml->setStretch(0, 0);
    ml->setStretch(1, 1);
    ml->setStretch(2, 0);
    this->setObjectName("ngbox");
    this->setLayout(ml);
    this->setMinimumSize({300, 50});

    connect(closeBtn,
            &QPushButton::released,
            this,
            &NotificationWidget::closed);
}

const Msg &NotificationWidget::msg() const
{
    return m_msg;
}

int NotificationWidget::id() const
{
    return m_msg.m_id;
}





}
