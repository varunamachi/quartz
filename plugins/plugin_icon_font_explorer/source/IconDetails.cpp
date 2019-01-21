#include <QVBoxLayout>
#include <QTreeView>
#include <QIcon>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

#include <common/iconstore/Icons.h>

#include "IconDetails.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

struct IconDetails::Data
{
    explicit Data(QWidget *parent)
        : m_icon(new QLabel(parent))
        , m_code(new QLineEdit(parent))
        , m_fontName(new QLineEdit(parent))
        , m_name(new QLineEdit(parent))
        , m_qzEnum(new QLineEdit(parent))
    {
        m_code->setReadOnly(true);
        m_fontName->setReadOnly(true);
        m_name->setReadOnly(true);
        m_qzEnum->setReadOnly(true);
    }

    QLabel *m_icon;

    QLineEdit *m_code;

    QLineEdit *m_fontName;

    QLineEdit *m_name;

    QLineEdit *m_qzEnum;

    QColor m_color = {};

    const IconInfo *m_iconInfo = nullptr;

};

IconDetails::IconDetails(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto grid = new QGridLayout();

    grid->addWidget(new QLabel(tr("Code"), this), 0, 0, 1, 1);
    grid->addWidget(m_data->m_code, 0, 1, 1, 2);

    grid->addWidget(new QLabel(tr("Font Name"), this), 1, 0, 1, 1);
    grid->addWidget(m_data->m_fontName, 1, 1, 1, 2);

    grid->addWidget(new QLabel(tr("Icon Name"), this), 2, 0, 1, 1);
    grid->addWidget(m_data->m_name, 2, 1, 1, 2);

    grid->addWidget(new QLabel(tr("Quartz Enum"), this), 3, 0);
    grid->addWidget(m_data->m_qzEnum, 3, 1);
    grid->addWidget(new QPushButton(getIcon(FAIcon::Copy), "", this), 3, 2);

    auto layout = new QHBoxLayout();
    layout->addWidget(m_data->m_icon);
    layout->addLayout(grid);
    this->setLayout(layout);

//    m_data->m_icon->setStyleSheet("background-color: black");
    m_data->m_icon->setMinimumSize({128, 128});
}

IconDetails::~IconDetails()
{

}

void IconDetails::setIconInfo(const IconInfo *info)
{
    m_data->m_iconInfo = info;
    if (info != nullptr) {
        auto icon = getIcon(info);
        m_data->m_icon->setPixmap(icon.pixmap({128, 128}));
        m_data->m_code->setText(info->m_strCode);
        m_data->m_fontName->setText(info->m_fontName);
        m_data->m_name->setText(info->m_name);
        m_data->m_qzEnum->setText(info->m_id);
    }
}



} } }
