#include <QStyle>
#include <QPushButton>

#include "../iconstore/IconFontStore.h"

#include "SearchBox.h"


namespace Quartz {

struct SearchBox::Data
{
    explicit Data(QWidget *parent)
        : m_clrBtn(new QPushButton(parent))
    {
        auto pixmap = getIcon(FAIcon::Broom).pixmap({32, 32});
        m_clrBtn->setIcon(pixmap);
        m_clrBtn->setFixedSize({32, 32});
    }

    QPushButton *m_clrBtn;
};


SearchBox::SearchBox( QWidget *parent)
    : QLineEdit(parent)
    , m_data(std::make_unique<Data>(parent))
{

    m_data->m_clrBtn->setCursor(Qt::ArrowCursor);
    m_data->m_clrBtn->setStyleSheet(
                "QPushButton { "
                    "border: none; "
                "}");
//    m_data->m_clrBtn->hide();

    connect( m_data->m_clrBtn,
             &QPushButton::clicked,
             this,
             &QLineEdit::clear);
    connect(this,
            &QLineEdit::textChanged,
            this,
            &SearchBox::updateCloseButton);
}

SearchBox::~SearchBox()
{

}


void SearchBox::setClearImage(const QIcon &icon)
{
    m_data->m_clrBtn->setIcon(icon);
}


void SearchBox::resizeEvent(QResizeEvent *)
{
//    int frameWidth = style()->pixelMetric( QStyle::PM_DefaultFrameWidth );
    QSize sz = m_data->m_clrBtn->size();
    auto rect = this->contentsRect();
//    mapToGlobal({rect.right()})
    m_data->m_clrBtn->move(rect.right() - sz.width(),
                           rect.bottom() - sz.height());
//    m_data->m_clrBtn->move((rect().right() - sz.width() / 2 + frameWidth),
//                           (rect().bottom()) - sz.height() + frameWidth);
}


void SearchBox::updateCloseButton(const QString& text)
{
//    m_data->m_clrBtn->setVisible(!text.isEmpty());
}

}
