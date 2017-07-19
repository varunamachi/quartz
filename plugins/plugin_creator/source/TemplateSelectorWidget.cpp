#include <QTreeView>
#include <QVBoxLayout>
#include <QLineEdit>

#include <common/model_view/CheckBoxDeligate.h>
#include <common/model_view/EditorDelegate.h>

#include "TemplateManager.h"
#include "TemplateSelectorWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateSelectorWidget::Data
{
    Data( TemplateSelectorWidget *parent )
        : m_filterEdit{ new QLineEdit{ parent }}
        , m_view{ new QTreeView{ parent }}
    {

    }

    QLineEdit *m_filterEdit;

    QTreeView *m_view;
};

TemplateSelectorWidget::TemplateSelectorWidget( QWidget* parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{
    auto main = new QVBoxLayout{ };
    main->addWidget( m_data->m_filterEdit );
    main->addWidget( m_data->m_view );

    m_data->m_view->setItemDelegateForColumn( 0, new CheckBoxDelegate{ this });
    m_data->m_view->setItemDelegateForColumn( 2, new EditorDelegate{ this });

    this->setLayout( main );
    main->setContentsMargins( QMargins{} );
    this->setContentsMargins( QMargins{} );
}

TemplateSelectorWidget::~TemplateSelectorWidget()
{

}

} } }
