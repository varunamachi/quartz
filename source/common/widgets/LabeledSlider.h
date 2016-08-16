#pragma once

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

namespace Vq { namespace Quartz {

class LabeledSlider : public QWidget
{
public:
    LabeledSlider( int defaultVal,
                   int minVal,
                   int maxVal,
                   QWidget *parent = nullptr )
        : QWidget( parent )
        , m_slider( new QSlider( this ))
        , m_label( new QLabel( this ))
    {
        m_slider->setMinimum( minVal );
        m_slider->setMaximum( maxVal );
        m_slider->setValue( defaultVal );
        QHBoxLayout *layout = new QHBoxLayout();
        layout->setContentsMargins( QMargins() );
        layout->addWidget( m_slider );
        layout->addWidget( m_label );

        connect( m_slider,
                 &QSlider::valueChanged,
                 [ = ]( int value ) {
            m_label->setText( QString( "%d" ).arg( value ));
        });
        setValue( 0 );
    }


    int value() const
    {
        return m_slider->value();
    }

    void setValue( int value )
    {
        m_slider->setValue( value );
        m_label->setText( QString( "%d" ).arg( value ));
    }

private:
    QSlider *m_slider;

    QLabel *m_label;
};

} }
