#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>

#include <common/model_view/CheckBoxDeligate.h>
#include <common/model_view/EditorDelegate.h>
#include <common/templating/TemplateInstance.h>
#include <common/templating/Template.h>
#include <common/widgets/QzTreeView.h>
#include <common/model_view/BasicSortFilter.h>

#include "TemplateManager.h"
#include "TemplateSelectorDialog.h"

namespace Quartz { namespace Ext { namespace Creator {

struct TemplateSelectorDialog::Data
{
    Data(TemplateManager *templateManager,
          TemplateSelectorDialog *parent)
        : m_templateManager(templateManager)
        , m_filterEdit(new QLineEdit(parent))
        , m_view(new QzTreeView(parent))
    {

    }

    TemplateManager *m_templateManager;

    QLineEdit *m_filterEdit;

    QzTreeView *m_view;

    //    QHash< TemplateInstance *, VarConfigWidget *> m_configWidgets;
};

TemplateSelectorDialog::TemplateSelectorDialog(
        TemplateManager *templateManager,
        QWidget* parent)
    : QDialog(parent)
    , m_data(std::make_unique<Data>(templateManager, this))
{
    auto basicFilter = new BasicSortFilter(this);
    basicFilter->setSourceModel(m_data->m_templateManager);
    m_data->m_view->setModel(basicFilter);

    auto okBtn = new QPushButton(tr("Select"), this);
    auto cancelBtn = new QPushButton(tr("Cancel"), this);
    auto selectBtn = new QPushButton(tr("Select All"), this);
    auto deselectBtn = new QPushButton(tr("Deelect All"), this);
    auto btnLyt = new QHBoxLayout{};
    btnLyt->addWidget(selectBtn);
    btnLyt->addWidget(deselectBtn);
    btnLyt->addStretch();
    btnLyt->addWidget(okBtn);
    btnLyt->addWidget(cancelBtn);

    auto main = new QVBoxLayout();
    main->addWidget(m_data->m_filterEdit);
    main->addWidget(m_data->m_view);
    main->addLayout(btnLyt);
    this->setLayout(main);
    this->setMinimumSize(QSize(500, 600));

    connect(okBtn, &QPushButton::released, [ this ](){
        this->accept();
    });
    connect(cancelBtn, &QPushButton::released, [ this ](){
        this->reject();
    });
    connect(selectBtn, &QPushButton::released, [ this ](){
        m_data->m_templateManager->selectAll();
    });
    connect(deselectBtn, &QPushButton::released, [ this ](){
        m_data->m_templateManager->deselectAll();
    });
    connect(m_data->m_filterEdit,
             &QLineEdit::textChanged,
             basicFilter,
             &BasicSortFilter::setExpression);
}

TemplateSelectorDialog::~TemplateSelectorDialog()
{

}

QVector< Template * > TemplateSelectorDialog::selectedTemplates() const
{
    QVector< Template * > selected;
    for (auto i = 0; i < m_data->m_templateManager->numTemplates(); ++ i) {
        auto t = m_data->m_templateManager->templateAt(i);
        if (t->isSelected()) {
            selected.append(t);
        }
    }
    return selected;
}

void TemplateSelectorDialog::clearSelection()
{
    for (auto i = 0; i < m_data->m_templateManager->numTemplates(); ++ i) {
        auto t = m_data->m_templateManager->templateAt(i);
        if (t != nullptr) {
            t->setSelected(false);
        }
//        m_data->m_templateManager->templateAt(i)->setSelected(false);
    }
}

} } }
