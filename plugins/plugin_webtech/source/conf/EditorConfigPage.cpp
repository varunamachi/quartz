
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QFile>

#include <common/generic_config/model/Config.h>
#include <common/generic_config/model/Param.h>
#include <common/generic_config/ops/ConfigParser.h>
#include <common/generic_config/ops/GenConfigUtils.h>
#include <common/generic_config/ui/GenConfigTreeModel.h>
#include <common/generic_config/ui/GenConfigWidget.h>

#include <plugin_base/PluginLogging.h>

#include "EditorConfigPage.h"
#include "conf/Conf.h"

namespace Quartz { namespace Ext { namespace WebTech {

struct EditorConfigPage::Data
{
    explicit Data(QWidget *parent)
        : m_view(new GenConfigWidget(parent))
    {

    }

    std::shared_ptr<Config> m_config;
    GenConfigWidget *m_view;
};

EditorConfigPage::EditorConfigPage(QWidget *parent)
    : QWidget (parent)
    , m_data(std::make_unique<Data>(this))
{


    auto lyt = new QVBoxLayout();
    lyt->addWidget(m_data->m_view);
//    lyt->addStretch();
    this->setLayout(lyt);

    auto valueProvider = [](const QString &key) -> QVariant {
        return confman()->retrieve(key, Conf::CONF_DOMAIN);
    };

    QFile file{":/resources/EditorSettings.xml"};
    if (file.open(QIODevice::ReadOnly)) {
        ConfigParser parser{valueProvider};
        auto configs = parser.parse(file.readAll());
        if (! configs.isEmpty()) {
            m_data->m_config = configs[0];
            m_data->m_view->setConfig(m_data->m_config.get());

        } else {
            QZP_ERROR << "Invalid config file EditorSettings.xml given";
        }
    } else {
        QZP_ERROR << "Failed to open editor setting XML";
    }
    refresh();

    connect(m_data->m_view->configModel(),
            &GenConfigTreeModel::dataChanged,
            [](const QModelIndex &idx, const QModelIndex &) {
        auto param = treenode_cast<Param *>(idx.data(Qt::UserRole));
        if (param != nullptr) {
            setConf(param->id(), param->value());
        }
    });

}

EditorConfigPage::~EditorConfigPage()
{
}

void EditorConfigPage::refresh()
{
    auto hash = confman()->allFromDomain(Conf::CONF_DOMAIN);
    m_data->m_view->configModel()->setValues(hash);
}





} } }
