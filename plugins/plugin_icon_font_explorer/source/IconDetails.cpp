#include <QVBoxLayout>
#include <QTreeView>
#include <QIcon>
#include <QLabel>

#include <common/iconstore/Icons.h>

#include "IconDetails.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

struct IconDetails::Data
{
    explicit Data(QWidget *parent)
        : m_icon(new QLabel(parent))
    {

    }

    QLabel *m_icon;

    QColor m_color = {};

    const IconInfo *m_iconInfo = nullptr;

};

IconDetails::IconDetails(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_data->m_icon);
    this->setLayout(layout);
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
    }
}



} } }
