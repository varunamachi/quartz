
#include <QPainter>
#include <QMainWindow>
#include <QCoreApplication>
#include <QToolButton>
#include <QMenu>
#include <QApplication>
#include <QCoreApplication>
#include <QRandomGenerator>

#include <core/logger/Logging.h>
#include <core/logger/AbstractLogDispatcher.h>
#include <core/ext/PluginManager.h>

#include <common/widgets/StackedSplitContainer.h>
#include <common/iconstore/IconFontStore.h>

#include <base/selector/Node.h>
#include <base/QzAppContext.h>
#include <base/action_bar/ActionBar.h>
#include <base/title_bar/TitleBar.h>
#include <base/view_manager/ViewManager.h>
#include <base/selector/SelectorManager.h>
#include <base/content_manager/ContentManager.h>
#include <base/general_selector/GeneralSelector.h>
#include <base/general_selector/GeneralNodeTree.h>
#include <base/settings/ConfigPageSelector.h>
#include <base/settings/ConfigPageManager.h>
#include <base/settings/BasicConfigPage.h>
#include <base/extension_details/PluginConfigPage.h>
#include <base/title_bar/QuartzItem.h>
#include <base/main_menu/MainMenuButton.h>
#include <base/explorer/FileSystemSelector.h>
#include <base/explorer/FileHandlerManager.h>
#include <base/notification/NotificationService.h>
#include <base/notification/msg.h>

#include "inbuilt/LogView.h"
#include "WelcomePage.h"
#include "QzMainWidget.h"
#include "AboutDialog.h"

namespace Quartz {

struct QzMainWidget::Data
{
    explicit Data(QWidget *parent)
        : m_roundedRect(true)
        , m_aboutDialog(new AboutDialog(parent))
    {

    }

    QString createStyleSheet();

    bool m_roundedRect;

    AboutDialog *m_aboutDialog;

    TitleBar *m_titleBar;

    SelectorManager *m_selector;

    ContentManager *m_content;

    ViewManager *m_viewManager;

    ActionBar *m_actionBar;

    QMenu *m_menu;

    std::unique_ptr<Ext::PluginManager> m_pluginManager;

};


QzMainWidget::QzMainWidget(QMainWindow *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    m_data->m_content   = new ContentManager(this);
    m_data->m_actionBar = new ActionBar(20, this);
    m_data->m_menu = new QMenu(this);
    this->setObjectName("quartz_widget");
    this->setContentsMargins({});

    auto viewContainer = new StackedSplitContainer(
                25,
                70,
                AbstractContainer::Position::After,
                Qt::Horizontal,
                this);
    viewContainer->setAutoSelectionPolicy(AutoSelectionPolicy::DoNotSelectAny);
    m_data->m_viewManager = new ViewManager(viewContainer, this);
    viewContainer->setContentWidget(
                m_data->m_content,
                AbstractContainer::Position::Before);
    viewContainer->setSizes(70, 300, 600);

    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    m_data->m_content->setSizePolicy(policy);

    auto selectorContainer = new StackedSplitContainer(
                50,
                50,
                AbstractContainer::Position::Before,
                Qt::Vertical,
                this);
    m_data->m_selector = new SelectorManager(selectorContainer, this);
    appContext()->setSelectorManager(m_data->m_selector);
    selectorContainer->setContentWidget(m_data->m_viewManager);
    selectorContainer->setSizes(20, 180, 600);

    auto mainMenu = new MainMenuButton(this);
    auto about = new QAction("About", this);
    connect(about, &QAction::triggered, [this]() {
       m_data->m_aboutDialog->exec();
    });
    mainMenu->addAction(about);
    mainMenu->setMaximumSize({50, 16});
    selectorContainer->addFixedWidget(mainMenu);

    auto nbtn = new QPushButton(getIcon(MatIcon::Notifications), "", this);
    viewContainer->addFixedWidget(nbtn, StackedSplitContainer::Position::After);
    auto ns = new NotificationService(nbtn);
    nbtn->setObjectName("nbtn");
    appContext()->setNotificationService(ns);
    connect(nbtn, &QPushButton::released, nbtn, []() {
        switch (QRandomGenerator::global()->bounded(3)) {
        case 0: showInfo("Quick brown fox jumped over the lazy dog"); break;
        case 1: showWarning("Quick brown fox jumped over the lazy dog"); break;
        case 2: showError("Quick brown fox jumped over the lazy dog"); break;
        };

//        showError("Quick brown fox");
    });

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_data->m_selector);
    mainLayout->addWidget(m_data->m_actionBar);
    mainLayout->setAlignment(m_data->m_actionBar, Qt::AlignBottom);
    mainLayout->setContentsMargins({});
    this->setLayout(mainLayout);
    this->setMinimumSize({800, 600});

    auto configPageManager = new ConfigPageManager(this);
    appContext()->setConfigPageManager(configPageManager);
    m_data->m_content->addContent(configPageManager);

    auto nodeSelector = new GeneralSelector(this);
    auto fhman = new FileHandlerManager(this);
    m_data->m_content->addContent(fhman);

    auto configTree = new ConfigPageSelector(this);
    configTree->addPage(new BasicConfigPage(configTree));

    auto logView = new LogView(this);
    m_data->m_viewManager->addView(logView);
    QZ_LOGGER()->dispatcher()->addTarget(logView);

    m_data->m_pluginManager = std::make_unique<Ext::PluginManager>();
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_actionBar);
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_selector);
    m_data->m_pluginManager->registerPluginAdapter(nodeSelector->model());
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_content);
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_viewManager);
    m_data->m_pluginManager->registerPluginAdapter(configTree);
    m_data->m_pluginManager->registerPluginAdapter(mainMenu);
    m_data->m_pluginManager->registerPluginAdapter(fhman);
    appContext()->setPluginManager(m_data->m_pluginManager.get());
    appContext()->setContentManager(m_data->m_content);
    auto execDir = QCoreApplication::applicationDirPath() + "/plugins";
    if (!m_data->m_pluginManager->loadFrom(execDir)) {
        QZ_ERROR("App") << "Failed to load all available plugins";
    }

    configTree->addPage(new Ext::PluginConfigPage(configTree));
    m_data->m_selector->addSelector(new FileSystemSelector(this));
    m_data->m_selector->addSelector(nodeSelector);
    m_data->m_selector->addSelector(configTree);

    const auto welcomeID = QStringLiteral("qz.welcome");
    m_data->m_content->addContent(
                new WelcomePage(welcomeID, m_data->m_content));
    m_data->m_content->selectContent(welcomeID);

}

QzMainWidget::~QzMainWidget()
{
    m_data->m_pluginManager->destroy();
    QZ_LOGGER()->dispatcher()->removeTarget(LogView::LOG_TARGET_ID);
}

void QzMainWidget::onAboutToQuit()
{

}

void QzMainWidget::setRoundedRect(bool useRoundedRect)
{
    m_data->m_roundedRect = useRoundedRect;
}

const TitleBar *QzMainWidget::titleBar() const
{
    return m_data->m_titleBar;
}


void QzMainWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    auto color = this->palette().color(QPalette::Background);
    if (m_data->m_roundedRect) {
        QPainterPath path;
        path.addRoundedRect(this->rect(), 5, 5);
        QBrush brush(color);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.fillPath(path, brush);
    }
    else {
        painter.fillRect(this->rect(), QBrush(color));
    }
}

}
