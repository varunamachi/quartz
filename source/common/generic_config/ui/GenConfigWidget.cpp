
#include <QTreeView>
#include <QVBoxLayout>

#include "../model/Config.h"
#include "GenConfigWidget.h"
#include "GenConfigTreeModel.h"
#include "GenConfigDelegate.h"

namespace Quartz {

struct GenConfigWidget::Data
{
    explicit Data( GenConfigTreeModel *model )
        : m_model{ model }
    {

    }

    GenConfigTreeModel *m_model;
};

GenConfigWidget::GenConfigWidget( Config *config, QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ new GenConfigTreeModel{ config, parent }}}
{
    auto layout = new QVBoxLayout{ this };
    auto view = new QTreeView{ this };
    //proxy model
    view->setModel( m_data->m_model );
    view->setItemDelegate( new GenConfigDelegate{ this });
    layout->addWidget( view );
    this->setLayout( layout );

    view->setContentsMargins( QMargins{} );
    layout->setContentsMargins( QMargins{} );
}

GenConfigWidget::~GenConfigWidget()
{

}

void GenConfigWidget::setConfig( Config *config )
{
    m_data->m_model->setConfig( config );
}



}
