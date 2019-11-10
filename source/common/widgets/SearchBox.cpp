#include <QStyle>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

#include "../iconstore/IconFontStore.h"

#include "SearchBox.h"

namespace Quartz {

struct SearchBox::Data {
    explicit Data(QWidget* parent)
        : m_editor(new QLineEdit(parent))
        , m_clrBtn(new QPushButton(parent)) {
        auto pixmap = getIcon(FAIcon::Broom).pixmap({20, 20});
        m_clrBtn->setIcon(pixmap);
        m_clrBtn->setFixedSize({20, 20});
        m_clrBtn->setObjectName("sbclrbtn");
        m_editor->setObjectName("scbox");
        m_clrBtn->setStyleSheet("QPushButton#sbclrbtn{"
                                "border: none;"
                                "padding: none;"
                                "margin: none;"
                                "}");
    }

    QLineEdit* m_editor;

    QPushButton* m_clrBtn;
};

SearchBox::SearchBox(QWidget* parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(parent)) {
    auto layout = new QHBoxLayout();
    layout->addWidget(m_data->m_editor);
    layout->addWidget(m_data->m_clrBtn);

    this->setLayout(layout);

    connect(m_data->m_editor,
            &QLineEdit::textChanged,
            this,
            [this](const QString& text) {
                emit this->textChanged(text);
            });
    connect(m_data->m_clrBtn,
            &QPushButton::released,
            m_data->m_editor,
            &QLineEdit::clear);
    m_data->m_editor->setContentsMargins({});
    m_data->m_clrBtn->setContentsMargins({});
    layout->setContentsMargins({});
    layout->setSpacing(0);
    this->setContentsMargins({});
}

SearchBox::~SearchBox() {
}

void SearchBox::setButtonIcon(const QIcon& icon) {
    m_data->m_clrBtn->setIcon(icon);
}

void SearchBox::setPlaceholderText(const QString& text) {
    m_data->m_editor->setPlaceholderText(text);
}

} // namespace Quartz
