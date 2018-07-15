#include <QSplitter>
#include <QList>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "QzScroller.h"
#include "StackedSplitContainer.h"

namespace Quartz {

struct StackedSplitContainer::Data
{
    QSplitter *m_splitter;

    QWidget *m_contentWidget;
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
    auto spor = orientation == Qt::Vertical ? Qt::Horizontal
                                            : Qt::Vertical;
    m_data->m_splitter = new QSplitter{ spor, this };
//    m_data->m_splitter->setStyleSheet(
//                "QSplitter::handle{ height: 1px; background: gray; }" );
    QSizePolicy policy;
    policy.setHorizontalPolicy( QSizePolicy::Expanding );
    policy.setVerticalPolicy( QSizePolicy::Expanding );
    m_data->m_splitter->setSizePolicy( policy );
    m_data->m_splitter->setContentsMargins( QMargins{} );
    if( selectorPosition == AbstractContainer::SelectorPosition::Before ) {
        m_data->m_splitter->addWidget(selector());
        m_data->m_splitter->addWidget(stackedWidget());
    }
    else {
        m_data->m_splitter->addWidget(stackedWidget());
        m_data->m_splitter->addWidget(selector());
    }
    this->setContentsMargins({});
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_data->m_splitter);
    layout->setContentsMargins({});
    this->setLayout(layout);
}

StackedSplitContainer::~StackedSplitContainer()
{

}

void StackedSplitContainer::setContentWidget(
        QWidget *widget,
        AbstractContainer::SelectorPosition position )
{
    if (position == AbstractContainer::SelectorPosition::Before) {
        m_data->m_splitter->insertWidget(0, widget);
    } else {
        m_data->m_splitter->addWidget(widget);
    }
    m_data->m_contentWidget = widget;
}

void StackedSplitContainer::setSizes( int selector, int stacked, int content )
{
    QList< int > sizes;
    sizes << selector << stacked << content;
    m_data->m_splitter->setSizes( sizes );
}

QString StackedSplitContainer::containerType() const
{
    return "StackedSplitContainer";
}

}
