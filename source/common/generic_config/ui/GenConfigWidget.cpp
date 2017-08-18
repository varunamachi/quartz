
#include <QTreeView>
#include <QVBoxLayout>

#include "../model/Config.h"
#include "GenConfigWidget.h"
#include "GenConfigTreeModel.h"

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
//    auto model =
    this->setLayout( layout );
}

GenConfigWidget::~GenConfigWidget()
{

}



}
