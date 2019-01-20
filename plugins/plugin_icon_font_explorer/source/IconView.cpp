#include <QVBoxLayout>
#include <QLineEdit>

#include <common/model_view/ArrayModel.h>
#include <common/model_view/BasicSortFilter.h>
#include <common/widgets/QzTreeView.h>


#include "IconDelegate.h"
#include "IconNode.h"
#include "IconView.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

const QVector<QString> HEADERS = {
    QObject::tr("Icon"),
    QObject::tr("Code"),
    QObject::tr("Name"),
    QObject::tr("Font"),
};

struct IconView::Data
{
    explicit Data(QWidget *parent)
        : m_view(new QzTreeView(parent))
        , m_searchBox(new QLineEdit(parent))
        , m_model(new ArrayModel(4, false, true, HEADERS, parent))
    {
        m_icons = IconNode::roots();
        m_proxy = new BasicSortFilter(parent);
        m_proxy->setSourceModel(m_model);
        m_view->setModel(m_proxy);
        m_view->setItemDelegateForColumn(0, new IconDelegate(parent));
        for (auto &ic : m_icons) {
            m_model->addRoot(ic.get());
        }
        m_searchBox->setPlaceholderText(tr("Search Icons"));
    }

    QzTreeView *m_view;

    QLineEdit *m_searchBox;

    ArrayModel *m_model;

    BasicSortFilter *m_proxy;

    QVector<std::shared_ptr<IconNode>> m_icons;
};

IconView::IconView(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(m_data->m_view);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_data->m_searchBox);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);

    connect(m_data->m_searchBox,
            &QLineEdit::textEdited,
            m_data->m_proxy,
            &BasicSortFilter::setExpression);
}

IconView::~IconView()
{

}



} } }
