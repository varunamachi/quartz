
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
//    explicit Data(QWidget *parent)
//        : m_themeBox(new QComboBox(parent))
//        , m_rulerBox(new QComboBox(parent))
//        , m_minimapShow(new QCheckBox(parent))
//        , m_lineNumShow(new QCheckBox(parent))
//    {
//    }
//    QGridLayout *createGrid(QWidget *parent) {
//        auto grid = new QGridLayout();
//        m_themeBox->addItem(tr("Dark"), "vs-dark");
//        m_themeBox->addItem(tr("Light"), "vs");
//        m_themeBox->addItem(tr("High Contrast"), "hc-black");
//        connect(m_themeBox,
//                qOverload<int>(&QComboBox::currentIndexChanged),
//                [this](int index) {
//            const auto &data = m_themeBox->itemData(index).toString();
//            if (!data.isEmpty()) {
//                setConf(Conf::EDITOR_THEME, data);
//            }
//        });
//        m_rulerBox->addItem(tr("80"), 80);
//        m_rulerBox->addItem(tr("100"), 100);
//        m_rulerBox->addItem(tr("120"), 120);
//        m_rulerBox->addItem(tr("None"), 0);
//        connect(m_rulerBox,
//                qOverload<int>(&QComboBox::currentIndexChanged),
//                [this](int index) {
//            auto data = m_rulerBox->itemData(index).toInt();
//            setConf<int>(Conf::EDITOR_VLINE_NUM, data);
//        });
//        connect(m_minimapShow,
//                &QCheckBox::clicked,
//                [](bool checked) {
//            setConf(Conf::EDITOR_SHOW_MINIMAP, checked);
//        });

//        connect(m_lineNumShow,
//                &QCheckBox::clicked,
//                [](bool checked) {
//           setConf(Conf::EDITOR_SHOW_LINENUM, checked) ;
//        });

//        grid->addWidget(new QLabel("Theme", parent), 0, 0);
//        grid->addWidget(m_themeBox, 0, 1);
//        grid->addWidget(new QLabel("Vertical Ruler (Num chars)", parent), 1, 0);
//        grid->addWidget(m_rulerBox, 1, 1);
//        grid->addWidget(new QLabel("Show minimap", parent), 2, 0);
//        grid->addWidget(m_minimapShow, 2, 1);
//        grid->addWidget(new QLabel("Show line numbers", parent), 3, 0);
//        grid->addWidget(m_lineNumShow, 3, 1);
//        grid->setColumnStretch(0, 0);
//        grid->setColumnStretch(1, 1);
//        return grid;
//    }
//    auto theme = conf<QString>(Conf::EDITOR_THEME, "vs-dark");
//    if (theme == "vs") {
//        m_data->m_themeBox->setCurrentIndex(1);
//    } else if (theme == "hc-black") {
//        m_data->m_themeBox->setCurrentIndex(2);
//    } else {
//        m_data->m_themeBox->setCurrentIndex(0);
//    }
//    auto lineNum = conf<int>(Conf::EDITOR_VLINE_NUM, 80);
//    if (lineNum == 0) {
//        m_data->m_rulerBox->setCurrentIndex(3);
//    } else {
//        auto numTxt = QString("%1").arg(lineNum);
//        m_data->m_rulerBox->setCurrentText(numTxt);
//    }
//    m_data->m_minimapShow->setChecked(
//                conf<bool>(Conf::EDITOR_SHOW_MINIMAP, false));
//    m_data->m_lineNumShow->setChecked(
//                conf<bool>(Conf::EDITOR_SHOW_LINENUM, true));
//    QComboBox *m_themeBox;
//    QComboBox *m_rulerBox;
//    QCheckBox *m_minimapShow;
//    QCheckBox *m_lineNumShow;
//    std::shared_ptr<Config> m_config;
//    GenConfigWidget *m_view;

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
    lyt->addStretch();
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
