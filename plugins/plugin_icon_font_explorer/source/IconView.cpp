#include <QVBoxLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QItemSelection>

#include <common/model_view/ArrayModel.h>
#include <common/model_view/BasicSortFilter.h>
#include <common/widgets/QzTreeView.h>

#include "IconProxyModel.h"
#include "IconDelegate.h"
#include "IconNode.h"
#include "IconView.h"
#include "IconDetails.h"

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
        , m_details(new IconDetails(parent))
        , m_model(new ArrayModel(3, false, true, HEADERS, parent))
    {
        m_icons = IconNode::roots();
        m_proxy = new IconProxyModel(parent);
        m_proxy->setSourceModel(m_model);
        m_view->setModel(m_proxy);
        m_view->setSelectionMode(QAbstractItemView::SingleSelection);
        m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_view->setItemDelegateForColumn(0, new IconDelegate(parent));
        for (auto &ic : m_icons) {
            m_model->addRoot(ic.get());
        }
        m_searchBox->setPlaceholderText(tr("Search Icons"));
        m_view->header()->setSectionResizeMode(
                    2, QHeaderView::ResizeToContents);
    }

    QzTreeView *m_view;

    QLineEdit *m_searchBox;

    IconDetails *m_details;

    ArrayModel *m_model;

    IconProxyModel *m_proxy;

    QVector<std::shared_ptr<IconNode>> m_icons;
};

IconView::IconView(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(m_data->m_view);
    bottomLayout->addWidget(m_data->m_details);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_data->m_searchBox);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);

    connect(m_data->m_searchBox,
            &QLineEdit::textEdited,
            m_data->m_proxy,
            &IconProxyModel::setExpression);
    connect(m_data->m_view->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            [this](const QItemSelection &sel, const QItemSelection &/*dsel*/ ) {
        auto indices = sel.indexes();
        if (indices.size() > 0) {
            auto tn = treenode_cast<IconNode *>(indices[0].data(Qt::UserRole));
            m_data->m_details->setIconInfo(tn->iconInfo());
        }
    });
}

IconView::~IconView()
{

}



} } }
