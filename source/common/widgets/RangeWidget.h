#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzCommon.h"

namespace Quartz {

class QUARTZ_COMMON_API RangeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RangeWidget( QWidget *parent = nullptr );

    ~RangeWidget();

    void setMax( int max );

    void setMin( int min );

    void setValue( int value );

    int value() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};



}
