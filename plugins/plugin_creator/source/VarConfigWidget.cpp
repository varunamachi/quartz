
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QGridLayout>

#include "Template.h"
#include "TemplateInstance.h"
#include "VarConfigWidget.h"


namespace Quartz { namespace Plugin { namespace Creator {

struct VarConfigWidget::Data
{
    explicit Data( TemplateInstance *ti, QWidget *parent )
        : m_ti{ ti }
        , m_layout{ new QGridLayout{ parent }}
    {

    }

    QMap< QString, QLineEdit *> m_editors;

    TemplateInstance *m_ti;

    QGridLayout *m_layout;

};

VarConfigWidget::VarConfigWidget( TemplateInstance *templInst,
                                  QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ templInst, this }}
{
    //iterate through template variables
    //create line editor for each variable
    //add it to layout and the map
    auto tmpl = templInst->instanceOf();
    for( auto i = 0; i < templInst->numChildren(); ++ i ) {
        auto &var = tmpl->variableAt( i );
        auto lab = new QLabel{ var.name(), this };
        auto txt = new QLineEdit{ var.defaultValue(), this };
        m_data->m_layout->addWidget( lab, i, 0 );
        m_data->m_layout->addWidget( txt, i, 1 );
        m_data->m_editors.insert( var.name(), txt );
        connect( txt,
                 &QLineEdit::textEdited,
                 [ = ]( const QString &text ){
            this->m_data->m_ti->setVariableValue( var.name(), text );
        });
    }
    this->setLayout( m_data->m_layout );
}

VarConfigWidget::~VarConfigWidget()
{

}



} } }
