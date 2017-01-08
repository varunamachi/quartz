
#include <QVBoxLayout>
#include <QTreeView>

#include <core/extension_system/AbstractPluginBundle.h>
#include <core/extension_system/PluginManager.h>


#include "../QzAppContext.h"
#include "BundleItemModel.h"
#include "PluginItemModel.h"
#include "BundleInfoPage.h"

namespace Quartz {

struct BundleInfoPage::Data
{
    Data( QWidget *parent )
        : m_bundle{ nullptr }
        , m_bundleModel{ new BundleItemModel{ BundleItemModel::NumCols::Two,
                                              parent }}
        , m_pluginModel{ new PluginItemModel{ parent }}
        , m_pluginView{ new QTreeView{ parent }}
        , m_dependencyView{ new QTreeView{ parent }}
    {
        m_pluginView->setModel( m_pluginModel );
        m_dependencyView->setModel( m_bundleModel );
    }

    const AbstractPluginBundle *m_bundle;

    BundleItemModel *m_bundleModel;

    PluginItemModel *m_pluginModel;

    QTreeView *m_pluginView;

    QTreeView *m_dependencyView;

    QVector< const AbstractPluginBundle *> m_deps;
};

const QString BundleInfoPage::CONTENT_ID{ "qz.bundlepage" };
const QString BundleInfoPage::CONTENT_NAME{ "Plugin Details" };
const QString BundleInfoPage::CONTENT_KIND{ "qz.info" };

BundleInfoPage::BundleInfoPage( QWidget *parent )
    : ContentWidget{ CONTENT_ID,
                     CONTENT_NAME,
                     CONTENT_KIND,
                     parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{ this };
    layout->addWidget( m_data->m_pluginView );
    layout->addWidget( m_data->m_dependencyView );
    this->setLayout( layout );

    m_data->m_pluginView->setContentsMargins( QMargins{} );
    m_data->m_dependencyView->setContentsMargins( QMargins{} );
    layout->setContentsMargins( QMargins{} );
    this->setContentsMargins( QMargins{} );
}

BundleInfoPage::~BundleInfoPage()
{

}

void BundleInfoPage::setBundle( const AbstractPluginBundle *bundle )
{
    if( bundle == nullptr ) {
        return;
    }
    m_data->m_bundle = bundle;
    m_data->m_deps.clear();
    const auto &depIds = bundle->dependencies();
    for( int i = 0; i < depIds.size(); ++ i ) {
        auto dep = appContext()->pluginManager()->bundle(
                    depIds.at( i ).first );
        if( dep != nullptr ) {
            m_data->m_deps.push_back( dep );
        }
    }
    m_data->m_pluginModel->setPluginList( &bundle->plugins() );
    m_data->m_bundleModel->setBundleList( &m_data->m_deps );
}



}

