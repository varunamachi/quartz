#include <QSplitter>
#include <QList>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>

#include "QzScroller.h"
#include "StackedSplitContainer.h"

namespace Quartz {

struct StackedSplitContainer::Data
{
    QSplitter *m_splitter = nullptr;

    QWidget *m_contentWidget = nullptr;

    QBoxLayout *m_qzLayout = nullptr;
};

StackedSplitContainer::StackedSplitContainer(
        int selectorDimention,
        int buttonDimention,
        AbstractContainer::SelectorPosition selectorPosition,
        Qt::Orientation orientation,
        QWidget *parent)
    : AbstractContainer(selectorDimention,
                        buttonDimention,
                        selectorPosition,
                        orientation,
                        parent)
    , m_data(std::make_unique<Data>())
{
//    auto spor = orientation == Qt::Vertical ? Qt::Horizontal
//                                            : Qt::Vertical;
//    if
    auto spor = Qt::Horizontal;
    auto wrapper = new QWidget(this);
    if (orientation == Qt::Vertical) {
        m_data->m_qzLayout = new QVBoxLayout();
        spor = Qt::Horizontal;
        wrapper->setMaximumWidth(selectorDimention);
    } else  {
        wrapper->setMaximumHeight(selectorDimention);
        m_data->m_qzLayout = new QHBoxLayout();
        spor = Qt::Vertical;
    }

    m_data->m_qzLayout->addWidget(selector());
    wrapper->setLayout(m_data->m_qzLayout);
    m_data->m_qzLayout->setSpacing(10);

    m_data->m_splitter = new QSplitter(spor, this);
    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    policy.setVerticalPolicy(QSizePolicy::Expanding);
    m_data->m_splitter->setSizePolicy(policy);

    if (selectorPosition == AbstractContainer::SelectorPosition::Before) {
        m_data->m_splitter->addWidget(wrapper);
        m_data->m_splitter->addWidget(stackedWidget());
    }
    else {
        m_data->m_splitter->addWidget(stackedWidget());
        m_data->m_splitter->addWidget(wrapper);
    }
    m_data->m_splitter->setChildrenCollapsible(false);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_data->m_splitter);
    this->setLayout(layout);
    m_data->m_splitter->setObjectName("selector-splitter");
    m_data->m_splitter->setStyleSheet(
                "QSplitter#selector-splitter::handle {width: 2px; }");

    this->setContentsMargins({});
    m_data->m_splitter->setContentsMargins({});
    layout->setContentsMargins({});
    m_data->m_qzLayout->setContentsMargins({});
    wrapper->setContentsMargins({});
}

StackedSplitContainer::~StackedSplitContainer()
{

}

void StackedSplitContainer::setContentWidget(
        QWidget *widget,
        AbstractContainer::SelectorPosition position)
{
    if (position == AbstractContainer::SelectorPosition::Before) {
        m_data->m_splitter->insertWidget(0, widget);
    } else {
        m_data->m_splitter->addWidget(widget);
    }
    m_data->m_contentWidget = widget;
}

void StackedSplitContainer::setSizes(int selector, int stacked, int content)
{
    QList<int> sizes;
    sizes << selector << stacked << content;
    m_data->m_splitter->setSizes(sizes);
}

QString StackedSplitContainer::containerType() const
{
    return "StackedSplitContainer";
}

void StackedSplitContainer::addFixedWidget(QWidget *widget)
{
    this->m_data->m_qzLayout->insertWidget(0, widget);
}

}
