
#include "EditorConfigPage.h"

namespace Quartz { namespace Ext { namespace WebTech {

struct EditorConfigPage::Data
{
    explicit Data(QWidget *parent)
    {

    }
};

EditorConfigPage::EditorConfigPage(QWidget *parent)
    : QWidget (parent)
    , m_data(std::make_unique<Data>(this))
{

}

EditorConfigPage::~EditorConfigPage()
{

}


} } }
