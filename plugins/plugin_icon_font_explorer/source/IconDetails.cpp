#include <QVBoxLayout>
#include <QTreeView>
#include <QIcon>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>

#include <common/iconstore/Icons.h>

#include "IconDetails.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

struct IconDetails::Data {
    explicit Data(QWidget* parent)
        : m_icon(new QLabel(parent))
        , m_code(new QLineEdit(parent))
        , m_fontName(new QLineEdit(parent))
        , m_name(new QLineEdit(parent))
        , m_qzGet(new QLineEdit(parent))
        , m_colorName(new QLineEdit(parent)) {
        m_code->setReadOnly(true);
        m_fontName->setReadOnly(true);
        m_name->setReadOnly(true);
        m_qzGet->setReadOnly(true);
        auto validator = new QRegExpValidator(parent);
        validator->setRegExp(QRegExp("^#(?:[0-9a-fA-F]){1,8}$"));
        m_colorName->setValidator(validator);
    }

    QLabel* m_icon;

    QLineEdit* m_code;

    QLineEdit* m_fontName;

    QLineEdit* m_name;

    QLineEdit* m_qzGet;

    QLineEdit* m_colorName;

    QColor m_color = {};

    const IconInfo* m_iconInfo = nullptr;
};

IconDetails::IconDetails(QWidget* parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this)) {
    auto copyBtn = new QPushButton(getIcon(FAIcon::Copy), "", this);
    copyBtn->setToolTip(tr("Copy Quartz getIcon function"));
    auto colorBtn = new QPushButton(getIcon(FAIcon::Palette), "", this);
    copyBtn->setToolTip(tr("Select a color for the icon"));
    auto colorReset = new QPushButton(getIcon(FAIcon::Broom), "", this);
    colorReset->setToolTip(tr("Reset color information"));

    auto grid = new QGridLayout();
    grid->addWidget(new QLabel(tr("Code"), this), 0, 0, 1, 1);
    grid->addWidget(m_data->m_code, 0, 1, 1, 3);

    grid->addWidget(new QLabel(tr("Font Name"), this), 1, 0, 1, 1);
    grid->addWidget(m_data->m_fontName, 1, 1, 1, 3);

    grid->addWidget(new QLabel(tr("Icon Name"), this), 2, 0, 1, 1);
    grid->addWidget(m_data->m_name, 2, 1, 1, 3);

    grid->addWidget(new QLabel(tr("Quartz Get"), this), 3, 0, 1, 1);
    grid->addWidget(m_data->m_qzGet, 3, 1, 1, 2);
    grid->addWidget(copyBtn, 3, 3, 1, 1);

    grid->addWidget(new QLabel(tr("Color"), this), 4, 0);
    grid->addWidget(m_data->m_colorName, 4, 1);
    grid->addWidget(colorReset, 4, 2);
    grid->addWidget(colorBtn, 4, 3);

    auto layout = new QHBoxLayout();
    layout->addWidget(m_data->m_icon);
    layout->addLayout(grid);
    this->setLayout(layout);

    m_data->m_icon->setMinimumSize({160, 128});

    connect(copyBtn, &QPushButton::clicked, [this]() {
        auto clipboard = QApplication::clipboard();
        clipboard->setText(m_data->m_qzGet->text());
    });
    connect(colorBtn, &QPushButton::clicked, [this]() {
        auto color = QColorDialog::getColor(m_data->m_color, this);
        if (color.isValid()) {
            m_data->m_color = color;
            this->update();
        }
    });
    connect(colorReset, &QPushButton::clicked, [this]() {
        m_data->m_color = QColor{};
        this->update();
    });
    connect(m_data->m_colorName, &QLineEdit::editingFinished, [this]() {
        const auto& colStr = m_data->m_colorName->text();
        if (colStr.size() % 2 != 0) {
            m_data->m_color = QColor(colStr);
            this->update();
        }
    });
}

IconDetails::~IconDetails() {
}

void IconDetails::setIconInfo(const IconInfo* info) {
    m_data->m_iconInfo = info;
    this->update();
}

void IconDetails::update() {
    if (m_data->m_iconInfo != nullptr) {
        QIcon icon;
        m_data->m_code->setText(m_data->m_iconInfo->m_strCode);
        m_data->m_fontName->setText(m_data->m_iconInfo->m_fontName);
        m_data->m_name->setText(m_data->m_iconInfo->m_name);
        if (m_data->m_color.isValid()) {
            icon = getIcon(m_data->m_iconInfo, m_data->m_color);
            m_data->m_colorName->setText(m_data->m_color.name(QColor::HexArgb));
            auto str = QString("getIcon(%1, QColor(%2, %3, %4, %5))")
                           .arg(m_data->m_iconInfo->m_id)
                           .arg(m_data->m_color.red())
                           .arg(m_data->m_color.green())
                           .arg(m_data->m_color.blue())
                           .arg(m_data->m_color.alpha());
            m_data->m_qzGet->setText(str);
        } else {
            icon = getIcon(m_data->m_iconInfo);
            auto str = QString("getIcon(%1)").arg(m_data->m_iconInfo->m_id);
            m_data->m_qzGet->setText(str);
            m_data->m_colorName->clear();
        }
        m_data->m_icon->setPixmap(icon.pixmap({150, 128}));
    }
}

}}} // namespace Quartz::Ext::IconFontExplorer
