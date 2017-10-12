
#include "TemplateConfigWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateConfigWidget::Data
{
    explicit Data( TemplateConfigWidget */*parent*/ )
    {

    }

};

TemplateConfigWidget::TemplateConfigWidget(  QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{

}

TemplateConfigWidget::~TemplateConfigWidget()
{

}



} } }
