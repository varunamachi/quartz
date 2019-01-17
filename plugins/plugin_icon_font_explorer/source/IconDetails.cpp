#include <QVBoxLayout>
#include <QTreeView>

#include "IconDetails.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

struct IconDetails::Data
{
    explicit Data(QWidget *parent)
    {

    }

};

IconDetails::IconDetails(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QHBoxLayout();
    this->setLayout(layout);
}

IconDetails::~IconDetails()
{

}



} } }
