#include <QSplitter>
#include <QList>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QApplication>
#include <QTextStream>
#include <QSizePolicy>

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
    selector()->setObjectName("selector");
    QString qss;
    QTextStream qssStream;
    qssStream.setString(&qss);
    auto col = QApplication::palette().text().color();
    auto col2 = QApplication::palette().color(QPalette::Midlight);
    col.setAlpha(30);
    qssStream << "border: none;"
                 "border-style: solid;"
                 "background-color: " << col2.name(QColor::HexArgb) << ";"
                 ;

    auto spor = Qt::Horizontal;
    auto wrapper = new QWidget(this);
    if (orientation == Qt::Vertical) {
        m_data->m_qzLayout = new QVBoxLayout();
        spor = Qt::Horizontal;
        wrapper->setMaximumWidth(selectorDimention);
        auto bpos = selectorPosition
                == AbstractContainer::SelectorPosition::Before
                ? "border-right-width: "
                : "border-left-width: ";
//            qssStream << bpos << "5px;";
    } else  {
        auto bpos = selectorPosition
                == AbstractContainer::SelectorPosition::Before
                ? "border-bottom-width: "
                : "border-top-width: ";
        wrapper->setMaximumHeight(selectorDimention);
        m_data->m_qzLayout = new QHBoxLayout();
        spor = Qt::Vertical;
//            qssStream << bpos << "1px;";
    }
    qssStream.flush();
    wrapper->setStyleSheet(qss);

    m_data->m_qzLayout->addWidget(selector());
    m_data->m_qzLayout->addStretch();
    wrapper->setLayout(m_data->m_qzLayout);

//    wrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    auto color = QApplication::palette().color(QPalette::Text);
    color.setAlpha(20);
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
    if (this->selectorPosition() == AbstractContainer::SelectorPosition::Before) {
        sizes << selector << stacked << content;
    } else {
        sizes << content << stacked << selector;
    }
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
