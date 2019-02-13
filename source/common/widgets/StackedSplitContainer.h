#pragma once

#include "StackedContainer.h"

namespace Quartz {

class QUARTZ_COMMON_API StackedSplitContainer : public AbstractContainer
{
    Q_OBJECT

public:
    explicit StackedSplitContainer(int selectorDimention,
                               int buttonDimention,
                               Position selectorPosition,
                               Qt::Orientation orientation,
                               QWidget *parent = nullptr);

    ~StackedSplitContainer() override;

    void setContentWidget(
            QWidget *widget,
            Position position = Position::After);

    void setSizes(int selector, int stacked, int content);

    QString containerType() const override;

    void addFixedWidget(QWidget *widget, Position position = Position::Before);

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};





}
