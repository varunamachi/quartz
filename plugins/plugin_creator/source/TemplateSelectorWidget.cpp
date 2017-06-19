#include <QTreeView>

#include "TemplateSelectorWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateSelectorWidget::Data
{
    Data( TemplateSelectorWidget *parent )
        : m_view{ new QTreeView{ parent }}
    {

    }

    QTreeView *m_view;

};

TemplateSelectorWidget::TemplateSelectorWidget( QWidget* parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{

}

TemplateSelectorWidget::~TemplateSelectorWidget()
{

}

} } }
