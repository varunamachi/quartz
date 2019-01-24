#include <QVBoxLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QItemSelection>
#include <QComboBox>
#include <QPushButton>

#include <common/model_view/ArrayModel.h>
#include <common/model_view/BasicSortFilter.h>
#include <common/widgets/QzTreeView.h>
#include <common/widgets/SearchBox.h>
#include <common/iconstore/Icons.h>

#include "IconProxyModel.h"
#include "IconDelegate.h"
#include "IconNode.h"
#include "IconView.h"
#include "IconDetails.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

const QVector<QString> HEADERS = {
    QObject::tr("Icon"),
    QObject::tr("Name"),
    QObject::tr("Font"),
};

struct IconView::Data
{
    explicit Data(QWidget *parent)
        : m_view(new QzTreeView(parent))
        , m_searchBox(new SearchBox(parent))
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

    SearchBox *m_searchBox;

    IconDetails *m_details;

    ArrayModel *m_model;

    IconProxyModel *m_proxy;

    QVector<std::shared_ptr<IconNode>> m_icons;
};

IconView::IconView(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto familySelector = new QComboBox(this);
    familySelector->addItem(
                "All",
                static_cast<int>(IconFontFamily::Any));
    familySelector->addItem(
                "Material",
                static_cast<int>(IconFontFamily::Material));
    familySelector->addItem(
                "Font Awesome",
                static_cast<int>(IconFontFamily::FontAwesome));
    familySelector->addItem(
                "Font Awesome Brands",
                static_cast<int>(IconFontFamily::FontAwesomeBrands));
    familySelector->setCurrentIndex(0);

    auto topLayout = new QHBoxLayout();
    topLayout->addWidget(m_data->m_searchBox);
    topLayout->addWidget(familySelector);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_data->m_view);
    mainLayout->addWidget(m_data->m_details);

    this->setLayout(mainLayout);

    connect(m_data->m_searchBox,
            &SearchBox::textChanged,
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
    connect(familySelector,
            qOverload<int>(&QComboBox::currentIndexChanged),
            [this, familySelector](int index) {
        auto data = familySelector->itemData(index);
        m_data->m_proxy->setFont(static_cast<IconFontFamily>(data.toInt()));
    });
}

IconView::~IconView()
{

}



} } }
