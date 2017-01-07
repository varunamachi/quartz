
#include <QVBoxLayout>
#include <QTreeView>

#include <core/extension_system/AbstractPluginBundle.h>
#include <core/extension_system/PluginManager.h>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"
#include "BundleInfoPage.h"
#include "BundleItemModel.h"
#include "BundleSelector.h"


namespace Quartz {

struct BundleSelector::Data
{
    explicit Data( QWidget *parent )
        : m_bundleModel{ new BundleItemModel{ BundleItemModel::NumCols::ONE,
                                              parent }}
        , m_bundleView{ new QTreeView{ parent }}
        , m_content{ new BundleInfoPage{ parent }}
    {

    }

    BundleItemModel *m_bundleModel;

    QTreeView *m_bundleView;

    BundleInfoPage *m_content;

    QVector< const AbstractPluginBundle *> m_bundles;
};

const QString BundleSelector::SELECTOR_ID{ "qz.bundle_selector" };
const QString BundleSelector::SELECTOR_NAME{ "Plugins" };


BundleSelector::BundleSelector( QWidget *parent )
    : AbstractSelector{ SELECTOR_ID, SELECTOR_NAME, parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{ this };
    layout->addWidget( m_data->m_bundleView );
    this->setLayout( layout );

    layout->setContentsMargins( QMargins{} );
    m_data->m_bundleView->setContentsMargins( QMargins{} );
    this->setContentsMargins( QMargins{} );

    appContext()->contentManager()->addContent( m_data->m_content );
    m_data->m_bundles = appContext()->pluginManager()->bundles();
    m_data->m_bundleModel->setBundleList( &m_data->m_bundles );
    m_data->m_bundleView->setModel( m_data->m_bundleModel );
}

BundleSelector::~BundleSelector()
{
    m_data->m_bundleModel->clear();
}

void BundleSelector::onSelected( const QModelIndex &index )
{
    appContext()->contentManager()->selectContent( BundleInfoPage::CONTENT_ID );
    auto bundle = static_cast< AbstractPluginBundle *>(
                index.internalPointer() );
    if( bundle != nullptr ) {
        m_data->m_content->setBundle( bundle );
    }
}



}
