#include <QTreeView>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>

#include <common/model_view/CheckBoxDeligate.h>
#include <common/model_view/EditorDelegate.h>
#include <common/templating/TemplateInstance.h>
#include <common/templating/Template.h>

#include "TemplateManager.h"
#include "TemplateSelectorDialog.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateSelectorDialog::Data
{
    Data( TemplateManager *templateManager,
          TemplateSelectorDialog *parent )
        : m_templateManager{ templateManager }
        , m_filterEdit{ new QLineEdit{ parent }}
        , m_view{ new QTreeView{ parent }}
    {

    }

    TemplateManager *m_templateManager;

    QLineEdit *m_filterEdit;

    QTreeView *m_view;

    //    QHash< TemplateInstance *, VarConfigWidget *> m_configWidgets;
};

TemplateSelectorDialog::TemplateSelectorDialog(
        TemplateManager *templateManager,
        QWidget* parent )
    : QDialog{ parent }
    , m_data{ new Data{ templateManager, this }}
{
    m_data->m_view->setModel( m_data->m_templateManager );
//    m_data->m_view->setItemDelegateForColumn( 0, new CheckBoxDelegate{ this });

    auto okBtn = new QPushButton{ tr( "Select" ), this };
    auto cancelBtn = new QPushButton{ tr( "Cancel"), this };
    auto btnLyt = new QHBoxLayout{};
    btnLyt->addStretch();
    btnLyt->addWidget( okBtn );
    btnLyt->addWidget( cancelBtn );

    auto main = new QVBoxLayout{ };
    main->addWidget( m_data->m_filterEdit );
    main->addWidget( m_data->m_view );
    main->addLayout( btnLyt );
    this->setLayout( main );
    this->setMinimumSize( QSize{ 500, 600 });

    connect( okBtn, &QPushButton::released, [ this ](){
        this->accept();
    });
    connect( cancelBtn, &QPushButton::released, [ this ](){
        this->reject();
    });
}


//void TemplateSelectorWidget::selected( const QModelIndex &index )
//{
//    if( ! index.isValid() ) {
//        return;
//    }
//    auto tn = static_cast< TreeNode *>( index.internalPointer() );
//    auto ti = dynamic_cast< TemplateInstance *>( tn );
//    if( ti != nullptr ) {
//        VarConfigWidget *vcw = nullptr;
//        if( m_data->m_configWidgets.contains( ti )) {
//            vcw = new VarConfigWidget{ ti, this };
//            m_data->m_configWidgets.insert( ti, vcw );
//            m_data->m_varConfigHolder->addWidget( vcw );
//        }
//        m_data->m_varConfigHolder->setCurrentWidget( vcw );
//    }
//}


TemplateSelectorDialog::~TemplateSelectorDialog()
{

}

QVector< Template * > TemplateSelectorDialog::selectedTemplates() const
{
    QVector< Template * > selected;
    for( auto i = 0; i < m_data->m_templateManager->numTemplates(); ++ i ) {
        auto t = m_data->m_templateManager->templateAt( i );
        if( t->isSelected() ) {
            selected.append( t );
        }
    }
    return selected;
}

void TemplateSelectorDialog::clearSelection()
{
    for( auto i = 0; i < m_data->m_templateManager->numTemplates(); ++ i ) {
        auto t = m_data->m_templateManager->templateAt( i );
        if( t != nullptr ) {
            t->setSelected( false );
        }
//        m_data->m_templateManager->templateAt( i )->setSelected( false );
    }
}

} } }
