#include <QTreeView>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <QLabel>

#include <common/model_view/CheckBoxDeligate.h>
#include <common/model_view/EditorDelegate.h>
#include <common/templating/TemplateInstance.h>
#include <common/templating/Template.h>

#include "TemplateManager.h"
#include "TemplateSelectorWidget.h"
#include "VarConfigWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateSelectorWidget::Data
{
    Data( TemplateManager *templateManager,
          TemplateSelectorWidget *parent )
        : m_templateManager{ templateManager }
        , m_filterEdit{ new QLineEdit{ parent }}
        , m_varConfigHolder{ new QStackedWidget{ parent }}
        , m_view{ new QTreeView{ parent }}
    {

    }

    TemplateManager *m_templateManager;

    QLineEdit *m_filterEdit;

    QStackedWidget *m_varConfigHolder;

    QTreeView *m_view;

    QHash< TemplateInstance *, VarConfigWidget *> m_configWidgets;
};

TemplateSelectorWidget::TemplateSelectorWidget(
        TemplateManager *templateManager,
        QWidget* parent )
    : QWidget{ parent }
    , m_data{ new Data{ templateManager, this }}
{
    auto main = new QGridLayout{ };
    main->addWidget( m_data->m_filterEdit, 0, 0 );
    main->addWidget( new QLabel{ this }, 0, 1 );
    main->addWidget( m_data->m_view, 1, 0 );
    main->addWidget( m_data->m_varConfigHolder, 1, 1 );

    m_data->m_view->setModel( m_data->m_templateManager );
    m_data->m_view->setItemDelegateForColumn( 0, new CheckBoxDelegate{ this });
    m_data->m_view->setItemDelegateForColumn( 2, new EditorDelegate{ this });

    this->setLayout( main );
    main->setContentsMargins( QMargins{} );
    this->setContentsMargins( QMargins{} );
}


void TemplateSelectorWidget::selected( const QModelIndex &index )
{
    if( ! index.isValid() ) {
        return;
    }
    auto tn = static_cast< ITreeNode *>( index.internalPointer() );
    auto ti = dynamic_cast< TemplateInstance *>( tn );
    if( ti != nullptr ) {
        VarConfigWidget *vcw = nullptr;
        if( m_data->m_configWidgets.contains( ti )) {
            vcw = new VarConfigWidget{ ti, this };
            m_data->m_configWidgets.insert( ti, vcw );
            m_data->m_varConfigHolder->addWidget( vcw );
        }
        m_data->m_varConfigHolder->setCurrentWidget( vcw );
    }
}


TemplateSelectorWidget::~TemplateSelectorWidget()
{

}

} } }
