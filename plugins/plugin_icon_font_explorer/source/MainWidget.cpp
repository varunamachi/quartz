
#include <QVBoxLayout>

#include "MainWidget.h"
#include "IconView.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

const QString MainWidget::CONTENT_ID("qzp.icon_font_explorer.content.main");
const QString MainWidget::CONTENT_NAME("IconFontExplorerMain");
const QString MainWidget::CONTENT_KIND("meta");

struct MainWidget::Data {
    Data(QWidget *parent)
        : m_iconView(new IconView(parent)) {

    }

    IconView *m_iconView;

};

MainWidget::MainWidget(QWidget *parent)
    : ContentWidget(CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent)
    , m_data(std::make_unique<Data>(this))
{
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_data->m_iconView);
    this->setLayout(mainLayout);
}

MainWidget::~MainWidget()
{

}


} } }
