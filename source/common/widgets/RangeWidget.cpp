#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

#include "RangeWidget.h"

namespace Quartz {

struct RangeWidget::Data
{
    Data( QWidget *parent )
        : m_slider{ new QSlider{ Qt::Horizontal, parent  }}
        , m_spinBox{ new QSpinBox{ parent }}
    {

    }

    QSlider *m_slider;

    QSpinBox *m_spinBox;
};

RangeWidget::RangeWidget( QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{

}

RangeWidget::~RangeWidget()
{

}

void RangeWidget::setMax( int max )
{
    if( max >= m_data->m_spinBox->minimum() ) {
        m_data->m_spinBox->setMaximum( max );
        m_data->m_slider->setMaximum( max );
    }
}

void RangeWidget::setMin( int min )
{
    if( min <= m_data->m_spinBox->maximum() ) {
        m_data->m_spinBox->setMinimum( min );
        m_data->m_slider->setMinimum( min );
    }
}

void RangeWidget::setValue( int value )
{
    if( value >= m_data->m_spinBox->minimum()
            && value <= m_data->m_spinBox->maximum() ) {
        m_data->m_spinBox->setValue( value );
        m_data->m_slider->setValue( value );
    }
}

int RangeWidget::value() const
{
    return m_data->m_spinBox->value();
}





}
