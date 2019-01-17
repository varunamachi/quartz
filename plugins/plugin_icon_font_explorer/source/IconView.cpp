#include <QVBoxLayout>
#include <QTreeView>

#include "IconView.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

struct IconView::Data
{
    explicit Data(QWidget *parent)
        : m_view(new QTreeView(parent))
    {

    }

    QTreeView *m_view;
};

IconView::IconView(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_data->m_view);
    this->setLayout(layout);
}

IconView::~IconView()
{

}



} } }
