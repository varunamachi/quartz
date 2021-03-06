
#include <QVBoxLayout>

#include "../model/Config.h"
#include "../../widgets/QzTreeView.h"
#include "GenConfigWidget.h"
#include "GenConfigTreeModel.h"
#include "GenConfigDelegate.h"

namespace Quartz {

struct GenConfigWidget::Data {
    explicit Data(GenConfigTreeModel* model)
        : m_model(model) {
    }

    GenConfigTreeModel* m_model;
};

GenConfigWidget::GenConfigWidget(QWidget* parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(new GenConfigTreeModel(parent))) {
    auto layout = new QVBoxLayout(this);
    auto view = new QzTreeView(this);
    // proxy model
    view->setModel(m_data->m_model);
    view->setItemDelegate(new GenConfigDelegate(this));
    view->setAlternatingRowColors(true);
    layout->addWidget(view);
    this->setLayout(layout);

    view->setContentsMargins(QMargins{});
    layout->setContentsMargins(QMargins{});
}

GenConfigWidget::~GenConfigWidget() {
}

void GenConfigWidget::setConfig(Config* config) {
    m_data->m_model->setConfig(config);
}

const GenConfigTreeModel* GenConfigWidget::configModel() const {
    return m_data->m_model;
}

GenConfigTreeModel* GenConfigWidget::configModel() {
    return m_data->m_model;
}

} // namespace Quartz
