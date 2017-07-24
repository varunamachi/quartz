
#include <QString>
#include <QLineEdit>
#include <QGridLayout>

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

VarConfigWidget::VarConfigWidget(TemplateInstance *templInst, QWidget *parent)
    : QWidget{ parent }
    , m_data{ new Data{ templInst, this }}
{
    //iterate through template variables
    //create line editor for each variable
    //add it to layout and the map

    this->setLayout( m_data->m_layout );

}



} } }
