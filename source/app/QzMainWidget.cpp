
#include <QPainter>
#include <QMainWindow>
#include <QCoreApplication>
#include <QToolButton>
#include <QMenu>
#include <QApplication>

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
#include <base/extension_details/PluginSelector.h>
#include <base/title_bar/QuartzItem.h>
#include <base/main_menu/MainMenuButton.h>

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

    std::unique_ptr< Ext::PluginManager > m_pluginManager;

};


QzMainWidget::QzMainWidget( bool drawWindowControls, QMainWindow *parent )
    : QWidget{ parent }
    , m_data(std::make_unique<Data>(this))
{
    m_data->m_titleBar  = new TitleBar(20, drawWindowControls, this);
//    m_data->m_titleBar->setContentsMargins(0, 10, 0, 5);
    m_data->m_content   = new ContentManager{ this };
    m_data->m_actionBar = new ActionBar{ 20, this };
    m_data->m_menu = new QMenu(this);
    this->setObjectName( "quartz_widget" );

    this->setContentsMargins( QMargins{} );

    QSizePolicy policy;
    policy.setHorizontalPolicy( QSizePolicy::Expanding );
//    policy.setVerticalPolicy( QSizePolicy::Expanding );

    m_data->m_content->setSizePolicy( policy );
    auto viewContainer = new StackedSplitContainer{
                20,
                70,
                AbstractContainer::SelectorPosition::After,
                Qt::Horizontal };
    viewContainer->setAutoSelectionPolicy(AutoSelectionPolicy::DoNotSelectAny);
    m_data->m_viewManager = new ViewManager( viewContainer, this );
    viewContainer->setContentWidget(
                m_data->m_content,
                AbstractContainer::SelectorPosition::Before );
    viewContainer->setSizes( 370, 210, 20 );

    auto selectorContainer = new StackedSplitContainer{
                40,
                40,
                AbstractContainer::SelectorPosition::Before,
                Qt::Vertical };
    m_data->m_selector = new SelectorManager(selectorContainer, this);
    appContext()->setSelectorManager( m_data->m_selector );
    selectorContainer->setContentWidget( m_data->m_viewManager );
    selectorContainer->setSizes(20, 180, 600);

    auto vlyt = new QHBoxLayout();
    vlyt->addWidget(m_data->m_titleBar);
    auto mainMenu = new MainMenuButton(this);
    vlyt->addWidget(mainMenu);

    auto about = new QAction(QIcon("://resources/quartz32.png"),
                             "About",
                             this);
    connect(about, &QAction::triggered, [this]() {
       m_data->m_aboutDialog->exec();
    });
    mainMenu->addAction(about);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(vlyt);
    mainLayout->addWidget( m_data->m_selector );
    mainLayout->addWidget( m_data->m_actionBar);
    mainLayout->setAlignment( m_data->m_actionBar, Qt::AlignBottom );
    mainLayout->setContentsMargins({ 0, 0, 1, 1 });
    mainLayout->setSpacing( 0 );
    this->setLayout( mainLayout );
    this->setMinimumSize({ 800, 600 });

    auto configPageManager = new ConfigPageManager{ this };
    appContext()->setConfigPageManager( configPageManager );
    m_data->m_content->addContent( configPageManager );

    auto nodeSelector = new GeneralSelector{ this };
    m_data->m_selector->addSelector( nodeSelector );
    auto configTree = new ConfigPageSelector{ this };
    m_data->m_selector->addSelector( configTree );
    configTree->addPage( new BasicConfigPage{ configTree });

    auto welcomeNode = nodeSelector->model()->addNode(
                QStringList(),
                tr("Welcome"),
                "qz.inbuilt.welcome",
                getIcon(MatIcon::Star));
    m_data->m_content->addContent(new WelcomePage(welcomeNode->nodeId(),
                                                  m_data->m_content));
    auto logView = new LogView(this);
    m_data->m_viewManager->addView(logView);
    QZ_LOGGER()->dispatcher()->addTarget(logView);

    m_data->m_pluginManager = std::make_unique<Ext::PluginManager>();
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_titleBar);
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_actionBar);
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_selector);
    m_data->m_pluginManager->registerPluginAdapter(nodeSelector->model());
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_content);
    m_data->m_pluginManager->registerPluginAdapter(m_data->m_viewManager);
    m_data->m_pluginManager->registerPluginAdapter(configTree);
    m_data->m_pluginManager->registerPluginAdapter(mainMenu);
    appContext()->setPluginManager(m_data->m_pluginManager.get());
    appContext()->setContentManager(m_data->m_content);
    auto execDir = QCoreApplication::applicationDirPath() + "/plugins";
    if (!m_data->m_pluginManager->loadFrom(execDir)) {
        QZ_ERROR( "App" ) << "Failed to load all available plugins";
    }

    auto pluginSelector = new Ext::PluginSelector{ this };
    m_data->m_selector->addSelector( pluginSelector );
    nodeSelector->setSelected(welcomeNode->nodeId());
}

QzMainWidget::~QzMainWidget()
{
    m_data->m_pluginManager->destroy();
    QZ_LOGGER()->dispatcher()->removeTarget( LogView::LOG_TARGET_ID );
}


TitleBar * QzMainWidget::titleBar()
{
    return m_data->m_titleBar;
}


void QzMainWidget::onAboutToQuit()
{

}

void QzMainWidget::setRoundedRect( bool useRoundedRect )
{
    m_data->m_roundedRect = useRoundedRect;
}


void QzMainWidget::paintEvent( QPaintEvent * /*event*/ )
{
    QPainter painter( this );
    auto color = this->palette().color( QPalette::Background );
    if( m_data->m_roundedRect ) {
        QPainterPath path;
        path.addRoundedRect(this->rect(), 5, 5);
        QBrush brush( color );
        painter.setRenderHint( QPainter::Antialiasing );
        painter.setRenderHint( QPainter::HighQualityAntialiasing );
        painter.fillPath( path, brush );
    }
    else {
        painter.fillRect( this->rect(), QBrush( color ));
    }
}

}
