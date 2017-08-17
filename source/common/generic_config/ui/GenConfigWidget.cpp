
#include "../model/Config.h"
#include "GenConfigWidget.h"

namespace Quartz {

struct GenConfigWidget::Data
{
    explicit Data( Config *config )
        : m_config{ config }
    {

    }

    Config *m_config;
};

GenConfigWidget::GenConfigWidget( Config *config, QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ config }}
{

}

GenConfigWidget::~GenConfigWidget()
{

}



}
