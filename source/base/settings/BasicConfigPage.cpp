
#include "BasicConfigPage.h"

namespace Quartz {

struct BasicConfigPage::Data
{

};

BasicConfigPage::BasicConfigPage( const QString &id,
                                  const QString &name,
                                  QWidget *parent )
    : AbstractConfigPage{ id, name, parent }
    , m_data{ new Data{} }
{

}

BasicConfigPage::~BasicConfigPage()
{

}

bool BasicConfigPage::apply()
{
    return false;
}

bool BasicConfigPage::setDefaults()
{
    return false;
}




}
