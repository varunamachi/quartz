#pragma once

#include "StackedContainer.h"

namespace Quartz {

class StackedSplitContainer : public AbstractContainer
{
    Q_OBJECT
public:
    explicit StackedSplitContainer( int selectorDimention,
                               int buttonDimention,
                               SelectorPosition selectorPosition,
                               Qt::Orientation orientation,
                               Qt::Orientation btnOriantation,
                               QWidget *parent = nullptr );

    ~StackedSplitContainer();

    void setContentWidget(
            QWidget *widget,
            SelectorPosition position = SelectorPosition::After );

    void setSizes( int selector, int stacked, int content );

    QString containerType() const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};





}
