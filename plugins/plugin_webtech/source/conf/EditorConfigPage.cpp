
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QFile>

#include <common/generic_config/model/ConfigParser.h>
#include <common/generic_config/model/Config.h>
#include <common/generic_config/ui/GenConfigTreeModel.h>
#include <common/generic_config/ui/GenConfigWidget.h>

#include <plugin_base/PluginLogging.h>

#include "EditorConfigPage.h"
#include "conf/Conf.h"

namespace Quartz { namespace Ext { namespace WebTech {

struct EditorConfigPage::Data
{
    explicit Data(QWidget *parent)
        : m_themeBox(new QComboBox(parent))
        , m_rulerBox(new QComboBox(parent))
        , m_minimapShow(new QCheckBox(parent))
        , m_lineNumShow(new QCheckBox(parent))
    {

    }

    QComboBox *m_themeBox;
    QComboBox *m_rulerBox;
    QCheckBox *m_minimapShow;
    QCheckBox *m_lineNumShow;
    std::shared_ptr<Config> m_config;


};

EditorConfigPage::EditorConfigPage(QWidget *parent)
    : QWidget (parent)
    , m_data(std::make_unique<Data>(this))
{
    auto grid = new QGridLayout();

    m_data->m_themeBox->addItem(tr("Dark"), "vs-dark");
    m_data->m_themeBox->addItem(tr("Light"), "vs");
    m_data->m_themeBox->addItem(tr("High Contrast"), "hc-black");
    connect(m_data->m_themeBox,
            qOverload<int>(&QComboBox::currentIndexChanged),
            [this](int index) {
        const auto &data = m_data->m_themeBox->itemData(index).toString();
        if (!data.isEmpty()) {
            setConf(Conf::EDITOR_THEME, data);
        }
    });

    m_data->m_rulerBox->addItem(tr("80"), 80);
    m_data->m_rulerBox->addItem(tr("100"), 100);
    m_data->m_rulerBox->addItem(tr("120"), 120);
    m_data->m_rulerBox->addItem(tr("None"), 0);
    connect(m_data->m_rulerBox,
            qOverload<int>(&QComboBox::currentIndexChanged),
            [this](int index) {
        auto data = m_data->m_rulerBox->itemData(index).toInt();
        setConf<int>(Conf::EDITOR_VLINE_NUM, data);
    });

    connect(m_data->m_minimapShow,
            &QCheckBox::clicked,
            [](bool checked) {
        setConf(Conf::EDITOR_SHOW_MINIMAP, checked);
    });

    connect(m_data->m_lineNumShow,
            &QCheckBox::clicked,
            [](bool checked) {
       setConf(Conf::EDITOR_SHOW_LINENUM, checked) ;
    });

    grid->addWidget(new QLabel("Theme", this), 0, 0);
    grid->addWidget(m_data->m_themeBox, 0, 1);
    grid->addWidget(new QLabel("Vertical Ruler (Num chars)", this), 1, 0);
    grid->addWidget(m_data->m_rulerBox, 1, 1);
    grid->addWidget(new QLabel("Show minimap", this), 2, 0);
    grid->addWidget(m_data->m_minimapShow, 2, 1);
    grid->addWidget(new QLabel("Show line numbers", this), 3, 0);
    grid->addWidget(m_data->m_lineNumShow, 3, 1);
    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);




//    parser->parse(
//    view->setModel(m_data->m_instanceProxy);
//    view->setRootIsDecorated(false);
//    configView->setModel(m_data->m_configProxy);
//    configView->setRootIsDecorated(false);
//    configView->setItemDelegate(new GenConfigDelegate(this));

    auto configView = new GenConfigWidget(this);
    auto lyt = new QVBoxLayout();
    lyt->addLayout(grid);
    lyt->addWidget(configView);
    lyt->addStretch();
    this->setLayout(lyt);

    QFile file{":/resources/EditorSettings.xml"};
    if (file.open(QIODevice::ReadOnly)) {
        ConfigParser parser;
        auto configs = parser.parse(file.readAll());
        if (! configs.isEmpty()) {
            m_data->m_config = configs[0];
            configView->setConfig(m_data->m_config.get());
        } else {
            QZP_ERROR << "Invalid config file EditorSettings.xml given";
        }
    } else {
        QZP_ERROR << "Failed to open editor setting XML";
    }
    refresh();
}

EditorConfigPage::~EditorConfigPage()
{
}

void EditorConfigPage::refresh()
{
    auto theme = conf<QString>(Conf::EDITOR_THEME, "vs-dark");
    if (theme == "vs") {
        m_data->m_themeBox->setCurrentIndex(1);
    } else if (theme == "hc-black") {
        m_data->m_themeBox->setCurrentIndex(2);
    } else {
        m_data->m_themeBox->setCurrentIndex(0);
    }

    auto lineNum = conf<int>(Conf::EDITOR_VLINE_NUM, 80);
    if (lineNum == 0) {
        m_data->m_rulerBox->setCurrentIndex(3);
    } else {
        auto numTxt = QString("%1").arg(lineNum);
        m_data->m_rulerBox->setCurrentText(numTxt);
    }

    m_data->m_minimapShow->setChecked(
                conf<bool>(Conf::EDITOR_SHOW_MINIMAP, false));
    m_data->m_lineNumShow->setChecked(
                conf<bool>(Conf::EDITOR_SHOW_LINENUM, true));
}





} } }
