#include <QPushButton>
#include <QHBoxLayout>
#include <QStyle>

#include <core/logger/Logging.h>

#include <common/widgets/QzScroller.h>

#include "QuartzItem.h"
#include "AbstractTitleItemProvider.h"
#include "TitleBar.h"

namespace Quartz {

const QString TitleBar::ADAPTER_NAME{ "qz.title_bar" };


TitleBar::TitleBar(
        int height,
        bool showWindowControls,
        QWidget *parent)
    : QWidget(parent)
    , m_height(height)

{
    m_scroller = new QzScroller(Qt::Horizontal, height, height, this);
    m_scroller->setContentsMargins({ 0, 5, 0, 5 });
    auto *layout = new QHBoxLayout();
    layout->setContentsMargins(QMargins());
    layout->addWidget(m_scroller, 1);
    if (showWindowControls) {
        auto minimizeBtn = new QPushButton(this);
        auto maxRestoreBtn = new QPushButton(this);
        auto closeBtn = new QPushButton(this);
        closeBtn->setIcon(style()->standardPixmap(
                              QStyle::SP_TitleBarCloseButton));
        minimizeBtn->setIcon(style()->standardPixmap(
                                 QStyle::SP_TitleBarMaxButton));
        maxRestoreBtn->setIcon(style()->standardPixmap(
                                   QStyle::SP_TitleBarMinButton));

        minimizeBtn->setMaximumSize(20, 20);
        maxRestoreBtn->setMaximumSize(20, 20);
        closeBtn->setMaximumSize(20, 20);
        minimizeBtn->setMinimumSize(20, 20);
        maxRestoreBtn->setMinimumSize(20, 20);

        auto btnWidget = new QWidget(this);
        auto btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->addWidget(minimizeBtn);
        btnLayout->addWidget(maxRestoreBtn);
        btnLayout->addWidget(closeBtn);
        btnWidget->setLayout(btnLayout);
        btnWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btnWidget->setContentsMargins(QMargins{});
        btnLayout->setContentsMargins(QMargins{});

        layout->addStretch();
        layout->addWidget(btnWidget, 0);
        closeBtn->setMinimumSize(20, 20);

        connect(closeBtn,
                 SIGNAL(clicked(bool)),
                 this,
                 SIGNAL(sigCloseRequested()));
        connect(maxRestoreBtn,
                 SIGNAL(clicked(bool)),
                 this,
                 SIGNAL(sigMaxRestoreRequested()));
        connect(minimizeBtn,
                 SIGNAL(clicked(bool)),
                 this,
                 SIGNAL(sigMinimizeRequested()));
    }

    this->setContentsMargins(QMargins(0, 0, 3, 3));
    this->setLayout(layout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


}

void TitleBar::addItem(QuartzItem *item)
{
    if (item != nullptr) {
        item->setMaximumHeight(m_height);
        item->setContentsMargins(QMargins{});
        m_items.insert(item->itemId(), item);
        m_scroller->addWidget(item);
        this->m_scroller->setVisible(true);
    }
}


void TitleBar::removeItem(QuartzItem *item)
{
    if (item != nullptr && m_items.contains(item->itemId())) {
        m_items.remove(item->itemId());
        m_scroller->removeWidget(item);
        delete item;
        if (m_items.size() == 0) {
            this->m_scroller->setVisible(false);
        }
    }
}


void TitleBar::removeItem(const QString &itemId)
{
    QuartzItem *item = m_items.value(itemId);
    if (item != nullptr) {
        m_items.remove(itemId);
        m_scroller->removeWidget(item);
        delete item;
    }
}


QList< QuartzItem * > TitleBar::items() const
{
    return m_items.values();
}


QList< QuartzItem * > TitleBar::items(const QString category)
{
    QList< QuartzItem *> filteredItems;
    for (QuartzItem *item : m_items.values()) {
        if (item->itemCategory() == category) {
            filteredItems.append(item);
        }
    }
    return filteredItems;
}


void TitleBar::removeCategory(const QString &category)
{
    QList< QuartzItem * > itemList = items(category);
    for (QuartzItem *item : itemList) {
        removeItem(item);
    }
}


void TitleBar::mouseDoubleClickEvent(QMouseEvent */*event*/)
{
    emit sigMaxRestoreRequested();
}

const QString & TitleBar::extensionType() const
{
    return  AbstractTitleItemProvider::EXTENSION_TYPE;
}

const QString & TitleBar::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool TitleBar::handleExtension(Ext::Extension *extension)
{
    bool result = false;
    auto itemProvider = dynamic_cast< AbstractTitleItemProvider *>(extension);
    if (itemProvider != nullptr) {
        auto items = itemProvider->titleItems();
        foreach(auto item, items) {
            addItem(item);
            m_extensionItems.push_back(item);
        }
        return true;
    }
    else {
        auto extensionName = extension != nullptr ? extension->extensionId()
                                            : "<null>";
        QZ_ERROR("Qz:TitleBar")
                << "Invalid titlebar extension provided: " << extensionName;
    }
    return result;
}

bool TitleBar::finalizeExtension()
{
//    for (int i = 0; i < m_extensionItems.size(); ++ i) {
//        auto item = m_extensionItems.at(i);
//        removeItem(item);
//    }
    m_extensionItems.clear();
    return  true;
}



}
