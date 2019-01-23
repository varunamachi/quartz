
#include <QSet>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QAction>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>

#include <core/logger/Logging.h>

#include <common/templating/Template.h>
#include <common/templating/TemplateInstance.h>
#include <common/model_view/ArrayModel.h>
#include <common/model_view/BasicSortFilter.h>
#include <common/generic_config/ui/GenConfigDelegate.h>
#include <common/generic_config/model/Config.h>
#include <common/generic_config/model/Param.h>
#include <common/widgets/QzTreeView.h>
#include <common/widgets/SearchBox.h>
#include <common/iconstore/IconFontStore.h>

#include "TemplateConfigWidget.h"
#include "TemplateManager.h"
#include "TemplateSelectorDialog.h"

namespace Quartz { namespace Ext { namespace Creator {

const QVector<QString> TI_HEADERS{
    QObject::tr("Instance")
};

struct TemplateConfigWidget::Data
{
    explicit Data(TemplateManager *tman, TemplateConfigWidget *parent)
        : m_tmodel(new ArrayModel(1, false, true, TI_HEADERS, parent))
        , m_instanceProxy(new BasicSortFilter(parent))
        , m_view(new QzTreeView(parent))
        , m_filter(new SearchBox(parent))
        , m_configModel(new ConfigModel(parent))
        , m_configProxy(new BasicSortFilter(parent))
        , m_configView(new QzTreeView(parent))
        , m_configFilter(new QLineEdit(parent))
        , m_addBtn(new QPushButton(getIcon(MatIcon::Add), "", parent))
        , m_removeBtn(new QPushButton(getIcon(MatIcon::Remove), "", parent))
        , m_clearBtn(new QPushButton(getIcon(MatIcon::Clear), "", parent))
        , m_tman(tman)
        , m_selector(new TemplateSelectorDialog(tman, parent))
        , m_emptyConfig("none", "None")
    {
        m_instanceProxy->setSourceModel(m_tmodel);
        m_configProxy->setSourceModel(m_configModel);
        m_filter->setPlaceholderText(tr("Filter Templates"));
        m_configFilter->setPlaceholderText(tr("Filter Vars"));
        m_addBtn->setToolTip(tr("Add template"));
        m_removeBtn->setToolTip(tr("Remove selected template"));
        m_clearBtn->setToolTip(tr("Clear all templates"));
    }

    ArrayModel *m_tmodel;
    BasicSortFilter *m_instanceProxy;
    QzTreeView *m_view;
    SearchBox *m_filter;

    ConfigModel *m_configModel;
    BasicSortFilter *m_configProxy;
    QzTreeView *m_configView;
    QLineEdit *m_configFilter;

    QPushButton *m_addBtn;
    QPushButton *m_removeBtn;
    QPushButton *m_clearBtn;

    TemplateManager *m_tman;
    TemplateSelectorDialog *m_selector;

    QHash< QString, std::shared_ptr<TemplateInstance>> m_instances;
    Config m_emptyConfig;
};

TemplateConfigWidget::TemplateConfigWidget(
        TemplateManager *tman,
        QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(tman, this))
{
    auto leftRightLayout = new QVBoxLayout();
    leftRightLayout->addStretch();
    leftRightLayout->addWidget(m_data->m_addBtn);
    leftRightLayout->addWidget(m_data->m_removeBtn);
    leftRightLayout->addWidget(m_data->m_clearBtn);
    leftRightLayout->addStretch();

    auto leftLeftLayout = new QVBoxLayout();
    leftLeftLayout->addWidget(new QLabel(tr("Selected Templates:"), this));
    leftLeftLayout->addWidget(m_data->m_filter);
    leftLeftLayout->addWidget(m_data->m_view);

    auto leftLayout = new QHBoxLayout();
    leftLayout->addLayout(leftLeftLayout);
    leftLayout->addLayout(leftRightLayout);

    auto rightLayout = new QVBoxLayout();
    rightLayout->addWidget(new QLabel(tr("Parameters:"), this));
    rightLayout->addWidget(m_data->m_configFilter);
    rightLayout->addWidget(m_data->m_configView);

    auto spacer = new QWidget();
    spacer->setMaximumWidth(20);
    spacer->setMinimumWidth(20);
    auto mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(spacer);
    mainLayout->addLayout(rightLayout);
    this->setLayout(mainLayout);

    m_data->m_view->setModel(m_data->m_instanceProxy);
    m_data->m_view->setRootIsDecorated(false);
    m_data->m_configView->setModel(m_data->m_configProxy);
//    m_data->m_configView->setModel(m_data->m_configModel);
    m_data->m_configView->setRootIsDecorated(false);
    m_data->m_configView->setItemDelegate(new GenConfigDelegate(this));

    connect(m_data->m_view->selectionModel(),
             &QItemSelectionModel::currentChanged,
             this,
             &TemplateConfigWidget::onSelection);
    connect(m_data->m_filter,
             &QLineEdit::textChanged,
             m_data->m_instanceProxy,
             &BasicSortFilter::setExpression);
    connect(m_data->m_configFilter,
             &QLineEdit::textChanged,
             m_data->m_configProxy,
             &BasicSortFilter::setExpression);
    connect(m_data->m_removeBtn,
            &QPushButton::clicked,
            this,
            &TemplateConfigWidget::clear);
    connect(m_data->m_addBtn, &QPushButton::clicked, [this](){
        m_data->m_selector->exec();
        if (m_data->m_selector->result() == QDialog::Accepted) {
            const auto selected = m_data->m_selector->selectedTemplates();
            foreach(auto t, selected) {
                this->createInstanceOf(t);
            }
        }
        m_data->m_selector->clearSelection();
    });
    connect(m_data->m_removeBtn, &QPushButton::clicked, [this](){
        auto selected = m_data->m_view->selectionModel()->selectedRows();
        for (auto index : selected) {
            auto node = m_data->m_tmodel->rootAt(index.row());
            m_data->m_tmodel->removeRoot(node);
        }
        m_data->m_selector->clearSelection();
    });
}

TemplateConfigWidget::~TemplateConfigWidget()
{

}

TemplateInstance * TemplateConfigWidget::createInstanceOf(Template *tmpl)
{
    auto name = tmpl->name();
    auto index = 1;
    //If there is a name clash, we suffix numbers
    do {
        if (! m_data->m_instances.contains(name)) {
            break;
        }
        name = tmpl->name() + "_" + QString::number(index);
        ++ index;
    } while (index <= 1000); //1000 should be enough
    auto inst = std::make_shared<TemplateInstance>(name,
                                                   tmpl->config()->clone(),
                                                   tmpl);
    m_data->m_instances.insert(name, inst);
    m_data->m_tmodel->addRoot(inst.get());
    return inst.get();
}

int TemplateConfigWidget::numInstances() const
{
    return m_data->m_tmodel->rootCount();
}

TemplateInstance * TemplateConfigWidget::instanceAt(int index)
{
    TemplateInstance *tinst = nullptr;
    if (index < m_data->m_tmodel->rootCount()) {
        tinst = static_cast< TemplateInstance * >(
                    m_data->m_tmodel->rootAt(index));
    }
    return tinst;
}

void TemplateConfigWidget::clear()
{
    m_data->m_tmodel->clear();
    m_data->m_instances.clear();
    m_data->m_configModel->setConfig(&m_data->m_emptyConfig);
}

void TemplateConfigWidget::onSelection(const QModelIndex &current,
                                        const QModelIndex &/*prev*/)
{
    auto node = current.data(Qt::UserRole).value<TreeNode *>();
    auto ti = dynamic_cast<TemplateInstance *>(node);
    if (ti != nullptr) {
        if (ti->instanceOf()->config() != nullptr) {
            m_data->m_configModel->setConfig(ti->instanceConfig());
        } else {
            m_data->m_configModel->setConfig(&m_data->m_emptyConfig);
        }
    }
}

//////////////////////// Config Model ///////////////////////////

const QVector<QString> CONFIG_HEADERS{
    QObject::tr("Name"),
    QObject::tr("Value")
};

ConfigModel::ConfigModel(QObject *parent)
    : AbstractTreeModel{
          parent,
          AbstractTreeModel::Options(2, false, true, CONFIG_HEADERS)}
    , m_config(nullptr)
{

}

ConfigModel::~ConfigModel()
{

}

void ConfigModel::setConfig(Config *config)
{
    beginResetModel();
    m_config = config;
    endResetModel();
}

TreeNode * ConfigModel::rootAt(int index) const
{
    if (m_config != nullptr && index < m_config->numChildParams()) {
        return m_config->childParamAt(index);
    }
    return nullptr;
}

int ConfigModel::rootCount() const
{
    if (m_config != nullptr) {
        return m_config->numChildParams();
    }
    return 0;
}


} } }
